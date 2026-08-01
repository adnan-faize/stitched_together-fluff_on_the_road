#pragma once

#ifdef STFR_STATIC_BUILD
    #define STFR_API
#else
    #ifdef STFR_OS_WINDOWS
        #if defined(STFR_CORE_BUILD) || defined(STFR_PLATFORM_BUILD) || defined(STFR_RENDERER_BUILD)
            #define STFR_API __declspec(dllexport)
        #else
            #define STFR_API __declspec(dllimport)
        #endif
    #else
        #define STFR_API __attribute__((visibility("default")))
    #endif
#endif
