#include "GpxContents.h"

#include "debug.h"


GpxContents::GpxContents(const std::string &filename) :
    _filename(filename),
    _creator(""),
    _version(""),
    _metadata(0)
{
    TRACE("Instantiated");
}


void GpxContents::setAttributes(const std::string &creator, const std::string &version)
{
    _creator = creator;
    _version = version;
}


void GpxContents::createMetadata()
{
    _metadata = new Metadata();
}


Metadata* GpxContents::getMetadata()
{
    return _metadata;
}


void Metadata::setLinkUrl(const std::string &link_url)
{
    _link_url = link_url;
}

void Metadata::setLinkText(const std::string &link_text)
{
    _link_text = link_text;
}

void Metadata::setTime(const std::string &time)
{
    _time = time;
}

void Metadata::setBounds(const std::string &maxlat, const std::string &maxlon, const std::string &minlat, const std::string &minlon)
{
    _bounds.maxlat = maxlat;
    _bounds.maxlon = maxlon;
    _bounds.minlat = minlat;
    _bounds.minlon = minlon;
}
