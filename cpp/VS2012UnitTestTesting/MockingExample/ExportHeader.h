
#pragma once

#ifdef MOCKINGEXAMPLE_EXPORTS
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT __declspec(dllimport)
#endif
