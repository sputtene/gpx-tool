#ifndef INC_XML_SAX_PARSER_BACKEND
#define INC_XML_SAX_PARSER_BACKEND

#include <string>

class XmlSaxParser;


class XmlSaxParserBackend
{
public:
    virtual ~XmlSaxParserBackend();

    // Interface methods
    virtual bool ParseFile(const std::string &filename) = 0;


protected:
    XmlSaxParserBackend() :
        _frontend(0)
    { }

    void setFrontend(XmlSaxParser * const frontend) { _frontend = frontend; }
    XmlSaxParser *frontend() { return _frontend; }

private:
    XmlSaxParser *_frontend;
};

#endif  // INC_XML_SAX_PARSER_BACKEND
