#include "XmlSaxParser.h"

#include "debug.h"
#include "common.h"

#include <cassert>

#include "irrxml-1.2/src/irrXML.h"


using namespace irr::io;

template <typename T> XmlSaxParser<T>::XmlSaxParser(unsigned int maxUnhandled) :
    _state(1),                      // insert empty string
    _maxUnhandled(maxUnhandled),
    _unhCount(0)
{ }


// Event handlers
template <typename T> void XmlSaxParser<T>::start(const std::string &name, const std::map<std::string, std::string> &attr)
{
    assert(name != "");
    assert(!_state.empty());

    _state.push_back(name);

    typedef std::vector<std::string>::const_iterator it_t;
    for (it_t begin_it = _state.begin(); begin_it != _state.end(); ++begin_it)
    {
        std::string state_path;
        for (it_t path_it = begin_it; path_it != _state.end(); ++path_it)
        {
            state_path += "?" + *path_it;
        }

        if (_dispatchStart.count(state_path))
        {
            DEBUG("Found handler for '" << state_path << "': " << (_dispatchStart[state_path] ? _dispatchStart[state_path] : " -- NOP"));
            if (_dispatchStart[state_path])
            {
                (this->*_dispatchStart[state_path])(name, attr);
            }
            return;
        }
    }

    error("No dispatch function for start of node '" + name + "'");
    unhandled("start", name + " " + lex_cast<std::string>(attr.count) + " attrs");
}

void XmlSaxParser::end(const std::string &name)
{
    unhandled("end",     name);
}

void XmlSaxParser::text(const std::string &data)
{
    unhandled("text",    data);
}

void XmlSaxParser::comment(const std::string &data)
{
    unhandled("comment", data);
}

void XmlSaxParser::cdata(const std::string &data)
{
    unhandled("cdata",   data);
}

void XmlSaxParser::unknown(const std::string &data)
{
    unhandled("unknown", data);
}

void XmlSaxParser::unhandled(const std::string &handler, const std::string &content = "<no content>")
{
    TRACE("unhandled node " << ++_unhCount << " (" << handler << "): '" << content << "'");
}


void XmlSaxParser::error(const std::string &msg)
{
    std::string state_trace;
    for (std::vector<std::string>::const_iterator it = _state.begin(); it != _state.end(); ++it)
    {
        state_trace += (*it == "") ? "<?xml>"
                                   : " -> <" + *it + ">";
    }

    // TODO: change to ERROR(...)
    WARN("Error parsing GPX file: state: '" << state_trace << "'; msg: " << msg);

    // TODO: make exception hierarchy
    throw msg;
}

}



// Methods
bool XmlSaxParser::ParseFile(const std::string &filename)
{
    IrrXMLReader* xml = createIrrXMLReader(filename.c_str());
    DEBUG("Reading GPX file '" << filename << "' with parser '" << xml << "'");

    _unhCount = 0;
    bool rootNodeParsed = false;
    while (xml && xml->read()
            && (_maxUnhandled > 0) && (_unhCount <= _maxUnhandled))
    {
        EXML_NODE   nodeType = xml->getNodeType();
        std::string nodeName = xml->getNodeName() ? xml->getNodeName() : "";
        std::string nodeData = xml->getNodeData() ? xml->getNodeData() : "";

        std::map<std::string, std::string> attributes;
        for (int i = 0; i < xml->getAttributeCount(); ++i)
        {
            // Duplicate attributes cannot exist in a well-formed
            // XML document, so don't check for them.
            attributes[xml->getAttributeName(i)] = xml->getAttributeValue(i);
        }

        // Work around parser limitation: it reports a BOM as EXN_TEXT before
        // the first node is parsed.
        if (!rootNodeParsed && (nodeType != EXN_ELEMENT))
        {
            DEBUG("Skipping over garbage in XML file");
            continue;
        }

        switch(nodeType)
        {
            case EXN_ELEMENT:
                start(nodeName, attributes);
                rootNodeParsed = true;
                if (xml->isEmptyElement()) end(nodeName);
                break;
            case EXN_ELEMENT_END:   end(nodeName);      break;
            case EXN_NONE:          assert(0);          break;
            case EXN_TEXT:          text(nodeName);     break;
            case EXN_COMMENT:       comment(nodeName);  break;
            case EXN_CDATA:         cdata(nodeName);    break;
            case EXN_UNKNOWN:       unknown(nodeData);  break;
        }
    }

    delete xml;

    return true;
}
