#include "GpxParser.h"
#include "GpxContents.h"

#include <cassert>


#include "debug.h"


// Static data members
std::map<std::string, GpxParser::StartHandler>   GpxParser::_startDispatch;
std::map<std::string, GpxParser::EndHandler>       GpxParser::_endDispatch;
std::map<std::string, GpxParser::TextHandler>    GpxParser::_textDispatch;
std::map<std::string, GpxParser::CommentHandler> GpxParser::_commentDispatch;
std::map<std::string, GpxParser::CDataHandler>   GpxParser::_cDataDispatch;
std::map<std::string, GpxParser::UnknownHandler> GpxParser::_unknownDispatch;

bool GpxParser::_dispatchInitialized = false;


// TODO: temp helper function -> remove
static void print_attrs(const std::map<std::string, std::string> &attrs)
{
    if (attrs.size() == 0)
    {
        DEBUG("- no attributes");
        return;
    }

    for (std::map<std::string, std::string>::const_iterator it = attrs.begin(); it != attrs.end(); ++it)
    {
        DEBUG("- " << (*it).first << ": '" << (*it).second << "'");
    }
}

// Constructor
GpxParser::GpxParser() :
    XmlSaxParser(10),
    _state(),
    _gpxContents(0)
{
    _state.push("?xml");
    DEBUG("GpxParser instantiated: " << this);

    if (!_dispatchInitialized)
    {
        initializeDispatch();
    }
}


void GpxParser::initializeDispatch()
{
    _startDispatch["gpx"]       = &GpxParser::start_gpx;
    _startDispatch["metadata"]  = &GpxParser::start_metadata;
    _startDispatch["link"]      = &GpxParser::start_link;

#if 0
    static std::map<States, StartHandler>   _startDispatch;
    static std::map<States, EndHandler>     _endDispatch;
    static std::map<States, TextHandler>    _textDispatch;
    static std::map<States, CommentHandler> _commentDispatch;
    static std::map<States, CDataHandler>   _cDataDispatch;
    static std::map<States, UnknownHandler> _unknownDispatch;
#endif
}

GpxContents GpxParser::ParseGpxFile(const std::string &filename)
{
    _gpxContents = new GpxContents(filename);
    ParseFile(filename);

    return *_gpxContents;
}


void GpxParser::start(const std::string &name, const std::map<std::string, std::string> &attr)
{
    assert(!_state.empty());

    // TODO: check state hierarchy in helper function instead of only
    // the first node name
    if (!_startDispatch.count(name))
    {
        error("No dispatch function for start of node '" + name + "'");
    }

    (this->*_startDispatch[name])(name, attr);

    _state.push(name);
}


void GpxParser::start_gpx(const std::string &name, const std::map<std::string, std::string> &attr)
{
    if (_state.size() != 1)
    {
        error("node <gpx> must be root node");
    }

    assert(attr.count("creator"));
    assert(attr.count("version"));

    // Can't use attr[...], because that returns a non-const value.
    // More info: http://stackoverflow.com/questions/687789/c-const-stdmap-reference-fails-to-compile
    _gpxContents->setAttributes(attr.find("creator")->second, attr.find("version")->second);
}


void GpxParser::start_metadata(const std::string &name, const std::map<std::string, std::string> &attr)
{
    if (_state.top() != "gpx")
    {
        error("node <metadata> must be a child of <gpx>");
    }

    _gpxContents->createMetadata();
}


void GpxParser::start_link(const std::string &name, const std::map<std::string, std::string> &attr)
{
    if (_state.top() != "metadata")
    {
        error("node <link> must be a child of <metadata>");
    }

    assert(attr.count("href"));
    _gpxContents->getMetadata()->setLinkUrl(attr.find("href")->second);

}


void GpxParser::error(const std::string &msg)
{
    // Reverse order of state stack, so we can print it in a
    // natural order.
    std::stack<std::string> rev_state;
    while (!_state.empty())
    {
        rev_state.push(_state.top());
        _state.pop();
    }

    // The ?xml state is always present, so there is at least
    // 1 element on the state stack
    std::string state_trace = rev_state.top();
    _state.push(rev_state.top());
    rev_state.pop();

    while(!rev_state.empty())
    {
        state_trace += " -> " + rev_state.top();

        _state.push(rev_state.top());
        rev_state.pop();
    }

    // TODO: change to ERROR(...)
    WARN("Error parsing GPX file: " << msg << std::endl
            << "\t" << state_trace);

    // TODO: make exception hierarchy
    throw msg;
}
