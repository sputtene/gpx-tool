#ifndef INC_GPX_PARSER_H
#define INC_GPX_PARSER_H

#include <string>
#include <stack>

#include "XmlSaxParser.h"

#include "debug.h"


class GpxContents;


class GpxParser : public XmlSaxParser
{
public:
    GpxParser();
    virtual ~GpxParser() {};

    GpxContents ParseGpxFile(const std::string &filename);

protected:
    virtual void start      (const std::string &name, const std::map<std::string, std::string> &attr);
#if 0
    virtual void end        (const std::string &name);
    virtual void text       (const std::string &data);
    virtual void comment    (const std::string &data);
    virtual void cdata      (const std::string &data);
    virtual void unknown    (const std::string &data);
#endif

private:
    // State handler callback types and handler dispatch tables
    typedef void (GpxParser::*StartHandler  )(const std::string &name, const std::map<std::string, std::string> &attr);
    typedef void (GpxParser::*EndHandler    )(const std::string &name);
    typedef void (GpxParser::*TextHandler   )(const std::string &data);
    typedef void (GpxParser::*CommentHandler)(const std::string &data);
    typedef void (GpxParser::*CDataHandler  )(const std::string &data);
    typedef void (GpxParser::*UnknownHandler)(const std::string &data);

    static void initializeDispatch();

    static std::map<std::string, StartHandler>   _startDispatch;
    static std::map<std::string, EndHandler>     _endDispatch;
    static std::map<std::string, TextHandler>    _textDispatch;
    static std::map<std::string, CommentHandler> _commentDispatch;
    static std::map<std::string, CDataHandler>   _cDataDispatch;
    static std::map<std::string, UnknownHandler> _unknownDispatch;

    static bool _dispatchInitialized;


    // State dependent handlers
    void start_gpx     (const std::string &name, const std::map<std::string, std::string> &attr);
    void start_metadata(const std::string &name, const std::map<std::string, std::string> &attr);
    void start_link    (const std::string &name, const std::map<std::string, std::string> &attr);


    void error(const std::string &msg = "<no message>");


    std::stack<std::string> _state;


    // objects that represent parts of the parsed GPX file
    GpxContents *_gpxContents;
};


#endif  // INC_XML_PARSER_H
