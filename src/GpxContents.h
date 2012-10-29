#ifndef INC_GPX_CONTENTS
#define INC_GPX_CONTENTS

#include <string>


// forward declarations of all subdata in GpxContents
class Metadata;


class GpxContents
{
public:
    GpxContents(const std::string &filename);

    void setAttributes(const std::string &creator, const std::string &version);

    void      createMetadata();
    Metadata* getMetadata();

private:
    std::string _filename;
    std::string _creator;
    std::string _version;

    Metadata *_metadata;
};


class Metadata
{
public:
    Metadata() :
        _link_url(""),
        _link_text(""),
        _time(""),
        _bounds()
    {};

    void setLinkUrl(const std::string &link_url);
    void setLinkText(const std::string &link_text);
    void setTime(const std::string &time);
    void setBounds(const std::string &maxlat, const std::string &maxlon, const std::string &minlat, const std::string &minlon);

private:
    std::string _link_url;
    std::string _link_text;
    std::string _time;
    struct Bounds {
        Bounds() : maxlat(""), maxlon(""), minlat(""), minlon("") {};

        std::string maxlat;
        std::string maxlon;
        std::string minlat;
        std::string minlon;
    } _bounds;
};

#endif  // INC_GPX_CONTENTS
