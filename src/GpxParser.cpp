#include "GpxParser.h"
#include "GpxContents.h"


GpxContents GpxParser::ParseGpxFile(const std::string &filename)
{
    ParseFile(filename);

    return GpxContents(filename);
}
