#pragma once

#if 1
#ifdef AUTOLINKDLL_EXPORTS
__declspec(dllexport) void Testcall();
#else
__declspec(dllimport) void Testcall();
#endif
#else
void Testcall();
#endif