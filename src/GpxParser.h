#ifndef INC_GPX_PARSER_H
#define INC_GPX_PARSER_H

#include <string>

#include "XmlSaxParser.h"

class XmlSaxParserBackend;
class GpxContents;


class GpxParser : public XmlSaxParser
{
public:
    GpxParser(XmlSaxParserBackend *xpb) :
        XmlSaxParser(xpb)
    { }
    virtual ~GpxParser() {};


    // Perform parsing
    virtual GpxContents ParseFile(const std::string &filename);
};


#endif  // INC_XML_PARSER_H
