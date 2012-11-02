#ifndef INC_GPX_PARSER_H
#define INC_GPX_PARSER_H

#include <string>
#include <vector>

#include "XmlSaxParser.h"

#include "debug.h"


class GpxContents;


class GpxParser : public XmlSaxParser<GpxParser>
{
public:
    GpxParser();
    virtual ~GpxParser() {};

    GpxContents ParseGpxFile(const std::string &filename);

private:
    // State dependent handlers
    void start_gpx     (const std::string &name, const std::map<std::string, std::string> &attr);
    void start_metadata(const std::string &name, const std::map<std::string, std::string> &attr);
    void start_link    (const std::string &name, const std::map<std::string, std::string> &attr);

    void initializeDispatch(const std::string &version);

    // objects that represent parts of the parsed GPX file
    GpxContents *_gpxContents;
};


#endif  // INC_XML_PARSER_H
