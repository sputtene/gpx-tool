#include "GpxTool.h"
#include "UserInterface.h"
#include "GpxParser.h"
#include "GpxContents.h"
#include "debug.h"

#include <cassert>


GpxTool *GpxTool::_instance = 0;

void GpxTool::Init(int argc, char **argv)
{
    assert(_instance == 0);

    _instance = new GpxTool(argc, argv);
}


void GpxTool::Setup(UserInterface *ui, XmlSaxParserBackend *xp)
{
    assert(_instance);

    _instance->_userInterface = ui;
    _instance->_gpxParser = new GpxParser(xp);
}

int GpxTool::MainLoop()
{
    assert(_instance);
    assert(_instance->_userInterface);

    return _instance->_userInterface->MainLoop();
}


void GpxTool::ReadGpxFiles(const std::vector<std::string> &filenames)
{
    assert(_instance);
    assert(_instance->_gpxParser);

    for (std::vector<std::string>::const_iterator it = filenames.begin(); it != filenames.end(); ++it)
    {
        DEBUG("- Reading file '" << *it << "'");
        GpxContents gpxContents = _instance->_gpxParser->ParseFile(*it);
    }
}

GpxTool::GpxTool(int argc, char **argv):
    _userInterface(0),
    _gpxParser(0)
{
    DEBUG("argc: " << argc);
    for (int i = 0; i < argc; ++i)
    {
        DEBUG("- argv[" << i << "]: '" << argv[i] << "'");
    }
    DEBUG("finished argv");
    //
}
