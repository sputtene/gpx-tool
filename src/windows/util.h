#ifndef INC_UTIL_H
#define INC_UTIL_H

#include <string>
#include <cassert>


// Convert UTF-8 to 16bit wchar_t
inline std::wstring utf8tows(const std::string &text)
{
    const char *mbtext = text.c_str();

    int wctextlen = MultiByteToWideChar(CP_UTF8, 0, mbtext, -1, NULL, 0);
    assert(wctextlen);

    wchar_t *wctext = new wchar_t[wctextlen];
    assert(MultiByteToWideChar(CP_UTF8, 0, mbtext, -1 , wctext, wctextlen));

    std::wstring wtext(wctext);
    delete[] wctext;

    return wtext;
}


// convert 16bit wchar_t to UTF-8
inline std::string wstoutf8(const std::wstring &wtext)
{
    const wchar_t *wctext = wtext.c_str();

    int mbtextlen = WideCharToMultiByte(CP_UTF8, 0, wctext, -1, NULL, 0, NULL, NULL);
    assert(mbtextlen);

    char *mbtext = new char[mbtextlen];
    assert(WideCharToMultiByte(CP_UTF8, 0, wctext, -1 , mbtext, mbtextlen, NULL, NULL));

    std::string text(mbtext);
    delete[] mbtext;

    return text;
}


#endif  // INC_UTIL_H
