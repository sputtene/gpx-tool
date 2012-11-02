#include "XmlSaxParser.h"

#include "debug.h"

#include <cassert>

#include "irrxml-1.2/src/irrXML.h"


using namespace irr::io;

XmlSaxParser::XmlSaxParser(unsigned int maxUnhandled) :
    _maxUnhandled(maxUnhandled)
{ }

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
