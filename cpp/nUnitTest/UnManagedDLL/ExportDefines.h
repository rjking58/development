#pragma once

#if !defined(_NO_EXPORT)
    #if defined(UNMANAGED_DLL_EXPORTS)
        #define UNMANAGED_DLL_API __declspec(dllexport)
    #else
        #define UNMANAGED_DLL_API __declspec(dllimport)
    #endif
#else
    #define UNMANAGED_DLL_API
#endif