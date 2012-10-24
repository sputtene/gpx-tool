#ifndef INC_XML_SAX_PARSER_H
#define INC_XML_SAX_PARSER_H

#include <cassert>
#include <string>

#include "XmlSaxParserBackend.h"


class XmlSaxParser
{
public:
    virtual ~XmlSaxParser();


protected:
    XmlSaxParser(XmlSaxParserBackend *backend) :
        _backend(backend)
    {
        assert(_backend);
    }

    XmlSaxParserBackend* backend() { return _backend; };

private:
    XmlSaxParserBackend *_backend;

};

#endif
