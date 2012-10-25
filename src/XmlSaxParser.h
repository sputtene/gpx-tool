#ifndef INC_XML_SAX_PARSER_H
#define INC_XML_SAX_PARSER_H

#include <string>

#include "common.h"

#include "debug.h"

class XmlSaxParser
{
public:
    virtual ~XmlSaxParser() {};

    // Start parsing
    bool ParseFile(const std::string &filename);
    bool ParseString(const std::string &xmlString);


protected:
    // SAX callback functions
    virtual void start      (const std::string &name) { TRACE("start: '" << name << "'"); return; };
    virtual void end        (const std::string &name) { TRACE("end: '" << name << "'"); return; };

    virtual void text       (const std::string &text) { TRACE("text: '" << text << "'"); return; };

    virtual void comment    (const std::string &comment) { TRACE("comment: '" << comment << "'"); return; };

    virtual void cdata      (const std::string &cdata) { TRACE("cdata: '" << cdata << "'"); return; };

    virtual void unknown    () { TRACE("unknown: ???"); return; };
};

#endif
