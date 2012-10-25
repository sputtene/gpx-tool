#ifndef INC_GPX_TOOL_H
#define INC_GPX_TOOL_H

#include <vector>
#include <string>

// Forward declarations
class UserInterface;
class GpxParser;

// Singleton: entry point for gpx-tool
// This class must be inited from main() or equivalent.
class GpxTool
{
public:
    // Setup
    static void Init(int argc, char **argv);
    static void Setup(UserInterface *ui);

    // Start processing
    static int MainLoop();

    static void ReadGpxFiles(const std::vector<std::string> &filenames);
private:
    GpxTool(int argc, char **argv);

    static GpxTool *_instance;

    UserInterface *_userInterface;
    GpxParser     *_gpxParser;
};

#endif // INC_GPX_TOOL_H
