#include "XmlSaxParser.h"

#include "debug.h"

#include <cassert>

#include "irrxml-1.2/src/irrXML.h"


using namespace irr::io;


bool XmlSaxParser::ParseFile(const std::string &filename)
{
    IrrXMLReader* xml = createIrrXMLReader(filename.c_str());
    DEBUG("Reading GPX file '" << filename << "' with parser '" << xml << "'");
    unsigned int node_count = 0;
    while (xml && xml->read())
    {
        switch(xml->getNodeType())
        {
            case EXN_ELEMENT:
            {
                // TODO: extract node attributes
                start(xml->getNodeName());
            }
                break;
            case EXN_ELEMENT_END:   this->end(xml->getNodeName());      break;
            case EXN_NONE:          assert(0);                          break;
            case EXN_TEXT:          this->text(xml->getNodeName());     break;
            case EXN_COMMENT:       this->comment(xml->getNodeName());  break;
            case EXN_CDATA:         this->cdata(xml->getNodeName());    break;
            case EXN_UNKNOWN:       this->unknown();                    break;
        }
        if (++node_count > 50) { delete xml; xml = 0; }
    }

    delete xml;

    return true;
}
