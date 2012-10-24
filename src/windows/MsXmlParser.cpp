#include "MsXmlParser.h"

#include "../GpxContents.h"

#include "SaxHandler.h"
#include "util.h"

#include <cassert>

#include "../debug.h"



//// TODO: SETUP
// CoInitialize(NULL);

//// TEARDOWN
// CoUninitialize();


bool MsXmlParser::ParseFile(const std::string &filename)
{
    TRACE("called with param '" << filename << "'");

    assert(_saxReader);


    std::cout << "Parsing document: " << filename << std::endl;

    HRESULT hr = _saxReader->parseURL(utf8tows(filename).c_str());

    std::cout << "Parse result code: " << hr << std::endl;


    return true;
}


MsXmlParser::MsXmlParser() :
    _saxReader(0),
    _saxHandler(new SaxHandler())
{
    HRESULT hr = CoCreateInstance(
            __uuidof(SAXXMLReader30),
            NULL,
            CLSCTX_ALL,
            __uuidof(ISAXXMLReader),
            (void **)&_saxReader);

    if(!FAILED(hr))
    {
        WARN("Error " << hr);
        _saxReader = 0;
        delete _saxHandler;
        _saxHandler = 0;

        throw "Error instantiating SAXXMLReader";
    }

    hr = _saxReader->putContentHandler(_saxHandler);
    hr = _saxReader->putErrorHandler(_saxHandler);

}

MsXmlParser::~MsXmlParser()
{
    if (_saxReader)
    {
        _saxReader->Release();
        _saxReader = 0;
    }
}
