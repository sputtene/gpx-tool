#include "GpxParser.h"
#include "GpxContents.h"

#include <cassert>

#include <vector>

#include "debug.h"


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
    _gpxContents(0)
{
    DEBUG("GpxParser instantiated: " << this);

    addDispatchStart("?gpx", &GpxParser::start_gpx);
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

    if (version == "1.0")
    {
        addDispatchStart("?gpx?name", 0);
    }
    else if (version == "1.1")
    {
        addDispatchStart("?gpx?metadata", &GpxParser::start_metadata);
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
