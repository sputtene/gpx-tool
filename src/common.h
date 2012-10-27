#ifndef INC_COMMON_H
#define INC_COMMON_H

// Macro to suppress warnings about unused variables
#ifdef UNUSED
#elif defined(__GNUC__)
#  define UNUSED(x) UNUSED_ ## x __attribute__((unused))
#elif defined(__LCLINT__)
#  define UNUSED(x) /*@unused@*/ x
#else
#  define UNUSED(x) (x)
#endif


#include <sstream>

class bad_lexical_cast {};

template<typename Target, typename Source>
    Target lex_cast(Source arg)
{
    std::stringstream interpreter;
    Target result;

    if(!(interpreter << arg) ||
            !(interpreter >> result) ||
            !(interpreter >> std::ws).eof())
        throw bad_lexical_cast();

    return result;
}

#endif
