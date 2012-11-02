#ifndef INC_XML_SAX_PARSER_H
#define INC_XML_SAX_PARSER_H

#include <string>
#include <map>
#include <vector>

#include "common.h"

#include "debug.h"


template <typename T> class XmlSaxParser
{
public:
    XmlSaxParser(unsigned int maxUnhandled = 0);
    virtual ~XmlSaxParser() {};

    // Start parsing
    bool ParseFile(const std::string &filename);
    bool ParseString(const std::string &xmlString);


protected:
    //// Callback dispatch related
    // Dispatch handler callback types
    typedef void (T::*StartHandler  )(const std::string &name, const std::map<std::string, std::string> &attr);
    typedef void (T::*EndHandler    )(const std::string &name);
    typedef void (T::*TextHandler   )(const std::string &data);
    typedef void (T::*CommentHandler)(const std::string &data);
    typedef void (T::*CDataHandler  )(const std::string &data);
    typedef void (T::*UnknownHandler)(const std::string &data);

    // Dispatch table management
    void addDispatchStart   (const std::string &path, StartHandler   handler);
    void addDispatchEnd     (const std::string &path, EndHandler     handler);
    void addDispatchText    (const std::string &path, TextHandler    handler);
    void addDispatchComment (const std::string &path, CommentHandler handler);
    void addDispatchCData   (const std::string &path, CDataHandler   handler);
    void addDispatchUnknown (const std::string &path, UnknownHandler handler);


private:
    // Parser state bookkeeping
    std::vector<std::string> _state;


    // Parser event functions
    void start      (const std::string &name, const std::map<std::string, std::string> &attr);
    void end        (const std::string &name);
    void text       (const std::string &data);
    void comment    (const std::string &data);
    void cdata      (const std::string &data);
    void unknown    (const std::string &data);

    void unhandled(const std::string &handler, const std::string &content = "<no content>");

    void error(const std::string &msg = "<no message>");

    // Parser dispatch tables
    std::map<std::string, StartHandler>   _dispatchStart;
    std::map<std::string, EndHandler>     _dispatchEnd;
    std::map<std::string, TextHandler>    _dispatchText;
    std::map<std::string, CommentHandler> _dispatchComment;
    std::map<std::string, CDataHandler>   _dispatchCData;
    std::map<std::string, UnknownHandler> _dispatchUnknown;


private:
    unsigned int _maxUnhandled;
    unsigned int _unhCount;
};

#endif
