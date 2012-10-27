#include "GpxParser.h"
#include "GpxContents.h"

#include <cassert>


#include "debug.h"


// Static data members
std::map<GpxParser::States, GpxParser::StartHandler>   GpxParser::_startDispatch;
std::map<GpxParser::States, GpxParser::EndHandler>     GpxParser::_endDispatch;
std::map<GpxParser::States, GpxParser::TextHandler>    GpxParser::_textDispatch;
std::map<GpxParser::States, GpxParser::CommentHandler> GpxParser::_commentDispatch;
std::map<GpxParser::States, GpxParser::CDataHandler>   GpxParser::_cDataDispatch;
std::map<GpxParser::States, GpxParser::UnknownHandler> GpxParser::_unknownDispatch;

bool GpxParser::_dispatchInitialized = false;



// Constructor
GpxParser::GpxParser() :
    XmlSaxParser(10),
    _state()
{
    _state.push(NONE);
    DEBUG("GpxParser instantiated: " << this);

    if (!_dispatchInitialized)
    {
        initializeDispatch();
    }
}


void GpxParser::initializeDispatch()
{
    _startDispatch[NONE] = &GpxParser::start_none;
    //_startDispatch[GPX]  = GpxParser::start_gpx;

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
    ParseFile(filename);

    return GpxContents(filename);
}


void GpxParser::start (const std::string &name, const std::map<std::string, std::string> &attr)
{
    assert(!_state.empty());

    if (!_startDispatch.count(_state.top()))
    {
        error("No dispatch function for start of node '" + name + "'");
    }

    (this->*_startDispatch[_state.top()])(name, attr);
}


void GpxParser::start_none(const std::string &name, const std::map<std::string, std::string> &attr)
{
V   if (name != "gpx")
    {
        error("Expected start node 'gpx'");
    }

}


void GpxParser::error(const std::string &msg)
{
    // Reverse order of state stack, so we can print it in a
    // natural order.
    std::stack<States> rev_state;
    while (!_state.empty())
    {
        rev_state.push(_state.top());
        _state.pop();
    }

    std::string state_trace;
    while(!rev_state.empty())
    {
        switch(rev_state.top())
        {
            case NONE: state_trace += "?xml"; break;
            case GPX:  state_trace += " → gpx"; break;
            default:   state_trace += " → (" + lex_cast<std::string>(rev_state.top()) + ")"; break;
        }

        _state.push(rev_state.top());
        rev_state.pop();
    }

    // TODO: change to ERROR(...)
    WARN("Error parsing GPX file: " << msg << std::endl
            << "\t" << state_trace);

    // TODO: make exception hierarchy
    throw msg;
}
