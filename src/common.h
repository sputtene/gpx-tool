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

#endif
