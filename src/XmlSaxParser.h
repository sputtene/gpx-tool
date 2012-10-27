#ifndef INC_XML_SAX_PARSER_H
#define INC_XML_SAX_PARSER_H

#include <string>
#include <map>

#include "common.h"

#include "debug.h"

class XmlSaxParser
{
public:
    XmlSaxParser(unsigned int maxUnhandled = 0);
    virtual ~XmlSaxParser() {};

    // Start parsing
    bool ParseFile(const std::string &filename);
    bool ParseString(const std::string &xmlString);


protected:
    // SAX callback functions
    virtual void start      (const std::string &name,
                             const std::map<std::string, std::string> &UNUSED(attr))
                                                        { unhandled("start",   name); };
    virtual void end        (const std::string &name)   { unhandled("end",     name); };
    virtual void text       (const std::string &data)   { unhandled("text",    data); };
    virtual void comment    (const std::string &data)   { unhandled("comment", data); };
    virtual void cdata      (const std::string &data)   { unhandled("cdata",   data); };
    virtual void unknown    (const std::string &data)   { unhandled("unknown", data); };

private:
    void unhandled(const std::string &handler, const std::string &content = "<no content>")
    {
        TRACE("unhandled node " << ++_unhCount << " (" << handler << "): '" << content << "'");
    }

    unsigned int _maxUnhandled;
    unsigned int _unhCount;
};

#endif
