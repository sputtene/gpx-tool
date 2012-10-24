#ifndef INC_DEBUG_H
#define INC_DEBUG_H

#   include <iostream>

#define INFO(x)  std::cerr << x << std::endl;
#define WARN(x)  INFO("WW " << x)
//#define ERROR(x) INFO("!! " << x)     // FIXME: /usr/i686-w64-mingw32/include/wingdi.h:70:0: note: this is the location of the previous definition

#ifdef NDEBUG
#   define TRACE(x)     /* do nothing */
#   define DEBUG(x)     /* do nothing */
#else
#   define TRACE(x)     INFO(__FILE__ << ":" << __LINE__ << ": TT (" << __func__ << ") " << x)
#   define DEBUG(x)     INFO(__FILE__ << ":" << __LINE__ << ": DD (" << __func__ << ") " << x)
#endif

#endif  //INC_DEBUG_H
