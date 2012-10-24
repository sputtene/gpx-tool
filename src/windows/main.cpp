#include "../common.h"

#include <windows.h>

#include <utility>
#include <cstdlib>
#include <cstdio>

#include "../debug.h"

#include "Gui.h"
#include "MsXmlParser.h"
#include "../GpxTool.h"


//// Forward declarations
// Command line handling
std::pair<int, wchar_t **> ConvertCommandline(const PTSTR& szCmdLine);


int APIENTRY _tWinMain(HINSTANCE hInst, HINSTANCE UNUSED(hPrevInst), PTSTR szCmdLine, int iCmdShow)
{
    // Set GUI parameters. This must be done before calling GpxTool_Init(),
    // because that will instantiate the GUI, which depends on these
    // parameters.
    Gui::Setup(hInst, iCmdShow);

    MsXmlParser::Setup();


    // Initialize GpxTool controller. This will create the GUI.
    std::pair<int, wchar_t **> argcv = ConvertCommandline(szCmdLine);
    GpxTool::Init(argcv.first, argcv.second);
    free(argcv.second);
    GpxTool::Setup(Gui::Instance(), MsXmlParser::Instance());

    return GpxTool::MainLoop();
}


std::pair<int, wchar_t **> ConvertCommandline(const PTSTR& szCmdLine)
{
    // Program name is argv[0]
    wchar_t *programName = new wchar_t[MAX_PATH];
    GetModuleFileName(NULL, programName, MAX_PATH);

    int argc = 1;
    size_t cmdLineLen = wcslen(programName) + 1;    // argv[0] (including terminating \0)

    // Count arguments
    DEBUG("Counting arguments");
    for (PTCHAR cmdLineChar = szCmdLine; *cmdLineChar != '\0';)
    {
        // Skip whitespace before real parameters
        while (*cmdLineChar == ' ')
        {
            DEBUG("  skipping whitespace");
            ++cmdLineChar;
        }

        // If we have not reached the end of the command line,
        // we found a parameter.
        // Reserve a space for the terminating \0 in argv.
        if (*cmdLineChar != '\0')
        {
            DEBUG("Found parameter: '" << *cmdLineChar << "'");
            ++argc;
            ++cmdLineLen;
            ++cmdLineChar;
        }

        // Skip over parameter
        while ((*cmdLineChar != ' ') && (*cmdLineChar != '\0'))
        {
            DEBUG("  skipping parameter character: '" << *cmdLineChar << "'");
            ++cmdLineChar;
            ++cmdLineLen;
        }
    }
    DEBUG("... done. argc: " << argc);

    // Allocate contiguous memory block for argv* and its contents
    DEBUG("Allocating memory block for argv")
    wchar_t **argv = (wchar_t**) malloc(argc * sizeof(wchar_t*) + cmdLineLen * sizeof(wchar_t));
    DEBUG("... done.");

    // Find arguments, store them and pointers to them in argv
    wchar_t **argvp = argv;                     // pointer to argv arguments
    wchar_t *argvps = (wchar_t*)(argvp + argc); // argv arguments themselves
    DEBUG("Argv pointers: argvp: " << &argvp << "; argvps: " << &argvps);

    // argv[0]: program name
    DEBUG("Storing argv[0] (" << programName << ")");
    argvp[0] = argvps;
    swprintf(argvps, L"%s", programName);
    argvps += wcslen(programName) + 1;
    DEBUG("... done.");

    // actual arguments
    size_t currArgc = 1;
    for (PTCHAR cmdLineChar = szCmdLine; *cmdLineChar != '\0';)
    {
        // Skip whitespace before actual parameter
        while (*cmdLineChar == ' ')
            ++cmdLineChar;

        // New argument found: put pointer in argv[]
        if (*cmdLineChar != '\0')
        {
            argvp[currArgc] = argvps;
            ++currArgc;
        }

        // Copy argument to space pointed to by argv[] while performing
        // conversion from w_char_t to char if needed.
        while ((*cmdLineChar != ' ') && (*cmdLineChar != '\0'))
        {
            swprintf(argvps++, L"%hc", *cmdLineChar++);
        }

        // ... and terminate with \0
        *argvps++ = '\0';
    }
    DEBUG("Stored " << currArgc << " arguments");

    return std::pair<int, wchar_t **>(argc, argv);
}
