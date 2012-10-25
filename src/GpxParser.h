#ifndef INC_GPX_PARSER_H
#define INC_GPX_PARSER_H

#include <string>

#include "XmlSaxParser.h"

#include "debug.h"


class GpxContents;


class GpxParser : public XmlSaxParser
{
public:
    GpxParser() { DEBUG("GpxParser instantiated: " << this); };
    virtual ~GpxParser() {};

    GpxContents ParseGpxFile(const std::string &filename);
};


#endif  // INC_XML_PARSER_H
