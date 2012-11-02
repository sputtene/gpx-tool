#include "GpxParser.h"
#include "GpxContents.h"

#include <cassert>

#include <vector>

#include "debug.h"


// Static data members
std::map<std::string, GpxParser::StartHandler>   GpxParser::_dispatchStart;
std::map<std::string, GpxParser::EndHandler>     GpxParser::_dispatchEnd;
std::map<std::string, GpxParser::TextHandler>    GpxParser::_dispatchText;
std::map<std::string, GpxParser::CommentHandler> GpxParser::_dispatchComment;
std::map<std::string, GpxParser::CDataHandler>   GpxParser::_dispatchCData;
std::map<std::string, GpxParser::UnknownHandler> GpxParser::_dispatchUnknown;

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
    _state(1),          // insert empty string
    _gpxContents(0)
{
    DEBUG("GpxParser instantiated: " << this);

    if (!_dispatchInitialized)
    {
        initializeDispatch();
    }
}


void GpxParser::dispatchHelper(const char** const &cc_path, const size_t &n, const StartHandler &UNUSED(handler))
{
    assert(n > 0);  // can't create a path without elements

    std::string path(cc_path[0]);
    for (size_t i = 1; i < n; ++i)
    {
        path += "?" + std::string(cc_path[i]);
    }

    DEBUG("Final path: '" << path << "'");


    return;
}

void GpxParser::initializeDispatch(const std::string &version)
{
    // PATH: path of nodenames, separated by a ?. To anchor a path to the
    // root of the document, start PATH with a ?.
#define ADD_DISPATCH(EVENT, PATH, HANDLER)                          \
    do {                                                            \
        _dispatch##EVENT [PATH] = HANDLER;                          \
    } while (false);

    TRACE("initializing dispatch table for GPX version '" << (version != "" ? version : "<default>") << "'");

    if (version == "")
    {
        ADD_DISPATCH(Start, "?gpx",          &GpxParser::start_gpx);
    }
    else if (version == "1.0")
    {
        ADD_DISPATCH(Start, "?gpx?name", 0);
    }
    else if (version == "1.1")
    {
        ADD_DISPATCH(Start, "?gpx?metadata", &GpxParser::start_metadata);
#if 0
        _startDispatch["gpx"]       = &GpxParser::start_gpx;
        _startDispatch["metadata"]  = &GpxParser::start_metadata;
        _startDispatch["link"]      = &GpxParser::start_link;
#endif
    }
    else
    {
        WARN("unknown GPX version: '" + version + "'");
        assert(0);
    }

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
    if (_gpxContents)
    {
        delete _gpxContents;
        _gpxContents = 0;
    }

    _gpxContents = new GpxContents(filename);
    ParseFile(filename);

    return *_gpxContents;
}


void GpxParser::start(const std::string &name, const std::map<std::string, std::string> &attr)
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
            DEBUG("Found handler for '" << state_path << "': " << _dispatchStart[state_path] << (_dispatchStart[state_path] ? "" : " -- NOP"));
            if (_dispatchStart[state_path])
            {
                (this->*_dispatchStart[state_path])(name, attr);
            }
            return;
        }
    }

    error("No dispatch function for start of node '" + name + "'");
}


void GpxParser::start_gpx(const std::string &name, const std::map<std::string, std::string> &attr)
{
    if (name == "gpx")
    {
        assert(attr.count("creator"));
        assert(attr.count("version"));

        // Can't use attr[...], because that returns a non-const value.
        // More info: http://stackoverflow.com/questions/687789/c-const-stdmap-reference-fails-to-compile
        _gpxContents->setAttributes(attr.find("creator")->second, attr.find("version")->second);

        initializeDispatch(attr.find("version")->second);
    }
    else if (name == "name")
    {
    }
}


void GpxParser::start_metadata(const std::string &UNUSED(name), const std::map<std::string, std::string> &UNUSED(attr))
{
    _gpxContents->createMetadata();
}


void GpxParser::start_link(const std::string &UNUSED(name), const std::map<std::string, std::string> &attr)
{
    assert(attr.count("href"));
    _gpxContents->getMetadata()->setLinkUrl(attr.find("href")->second);

}


void GpxParser::error(const std::string &msg)
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
