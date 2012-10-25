#include "../common.h"

#include <windows.h>

#include <utility>
#include <cstdlib>
#include <cstdio>

#include "../debug.h"

#include "../GpxTool.h"
#include "Gui.h"
#include "util.h"


//// Forward declarations
// Command line handling
std::pair<int, char **> ConvertCommandline(wchar_t * const &szCmdLine);


int APIENTRY wWinMain(HINSTANCE hInst, HINSTANCE UNUSED(hPrevInst), wchar_t *szCmdLine, int iCmdShow)
{
    // Set GUI parameters. This must be done before calling GpxTool_Init(),
    // because that will instantiate the GUI, which depends on these
    // parameters.
    Gui::Setup(hInst, iCmdShow);


    // Initialize GpxTool controller. This will create the GUI.
    std::pair<int, char **> argcv = ConvertCommandline(szCmdLine);
    GpxTool::Init(argcv.first, argcv.second);
    free(argcv.second);
    GpxTool::Setup(Gui::Instance());

    return GpxTool::MainLoop();
}


std::pair<int, char **> ConvertCommandline(wchar_t * const &szCmdLine)
{
    // Program name is argv[0]
    wchar_t *programName = new wchar_t[MAX_PATH];
    GetModuleFileName(NULL, programName, MAX_PATH);

    // FIXME: Change logic so the following happens:
    //   std::vector<std::string> cmdLine("");
    //   cmdLine.push_back(programName);
    //   size_t cmdLineLen = programName.length() + 1; // include terminating \0
    //
    //   for (all arguments in szCmdLine) {
    //     std::string mbArg = wstoutf8(arg);
    //     cmdLine.push_back(mbArg);
    //     cmdLineLen += mbArg.length() + 1;
    //   }
    //
    //   argc = cmdLine.size();
    //   argv = malloc(...);
    //   for (it = cmdLine.begin() .. cmdLine.end()) {
    //     snprintf(argv, *it.length() + 1, "%s", *it.c_str());
    //     argv += *it.length() + 1;
    //   }
    //   return std::pair<...,...>(argc, argv);
    int argc = 1;
    size_t cmdLineLen = wcslen(programName) + 1;    // argv[0] (including terminating \0)

    // Count arguments
    DEBUG("Counting arguments");
    for (const wchar_t *cmdLineChar = szCmdLine; *cmdLineChar != L'\0';)
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
    char **argv = (char**) malloc(argc * sizeof(char*) + cmdLineLen * sizeof(char));
    DEBUG("... done.");

    // Find arguments, store them and pointers to them in argv
    char **argvp = argv;                    // pointer to argv arguments
    char *argvps = (char*)(argvp + argc);   // argv arguments themselves
    DEBUG("Argv pointers: argvp: " << &argvp << "; argvps: " << &argvps);

    // argv[0]: program name
    DEBUG("Storing argv[0] (" << programName << ")");
    argvp[0] = argvps;
    sprintf(argvps, "%s", wstoutf8(programName).c_str());
    argvps += wcslen(programName) + 1;
    DEBUG("... done.");

    // actual arguments
    size_t currArgc = 1;
    for (const wchar_t *cmdLineChar = szCmdLine; *cmdLineChar != L'\0';)
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
        // conversion from w_char_t to char.
        std::wstring wsCmdLineArg(L"");
        while ((*cmdLineChar != ' ') && (*cmdLineChar != '\0'))
        {
            wsCmdLineArg += *cmdLineChar++;
        }
        std::string mbCmdLineArg = wstoutf8(wsCmdLineArg);
        sprintf(argvps, "%s", mbCmdLineArg.c_str());
        argvps += sprintf(argvps, "%hc", *cmdLineChar++);

        // ... and terminate with \0
        *argvps++ = '\0';
    }
    DEBUG("Stored " << currArgc << " arguments");

    return std::pair<int, char **>(argc, argv);
}
