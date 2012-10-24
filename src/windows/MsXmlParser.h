#ifndef INC_MS_XML_PARSER
#define INC_MS_XML_PARSER

#include "../XmlSaxParserBackend.h"

#include <msxml2.h>

class SaxHandler;

class MsXmlParser : public XmlSaxParserBackend
{
public:
    MsXmlParser();
    virtual ~MsXmlParser();


    // Interface implementation
    virtual bool ParseFile(const std::string &filename);


private:
    // SAX reader class
    ISAXXMLReader* _saxReader;
    SaxHandler*    _saxHandler;
};

#endif  // INC_MS_XML_PARSER
