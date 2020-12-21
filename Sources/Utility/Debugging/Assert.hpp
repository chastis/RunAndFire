#pragma once

#include <sstream>
#define NOMINMAX
#include <windows.h> //TODO: move to platform folder
#include <iostream>

//#TODO : make crossplatform
#if defined(DEBUG)
    #define M42_ASSERT(cond, message)                                                                               \
        do {                                                                                                        \
            if (!(bool(cond)))                                                                                      \
            {                                                                                                       \
                std::wstringstream ss;                                                                              \
                ss << "Assertion failed: " << #cond << " in file " << __FILE__ << " at line " << __LINE__ << "!\n"; \
                ss << message << '\n';                                                                              \
                ss << "Press Try Again to break in debugger.";                                                      \
                int res = MessageBox(NULL,                                                                          \
                                     ss.str().c_str(),                                                              \
                                     L"Assertion failed!",                                                           \
                                     MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2);                        \
                if (res == IDTRYAGAIN)                                                                              \
                {                                                                                                   \
                    __debugbreak();                                                                                 \
                }                                                                                                   \
            }                                                                                                       \
        } while(0)
#else
#define M42_ASSERT(cond, message) \
    std::cout << message << "\n"; 
#endif //DEBUG