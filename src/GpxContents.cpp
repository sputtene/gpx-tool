#include "GpxContents.h"

#include "debug.h"

GpxContents::GpxContents(std::string filename)
    : _filename(filename)
{
    TRACE("called with param '" << filename << "'");
}
