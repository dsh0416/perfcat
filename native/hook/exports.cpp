#include "pch.hpp"

#ifdef _WIN32
#define EXPORTS_API __declspec(dllexport) __cdecl
#else
#define EXPORTS_API
#endif

extern "C" {
void EXPORTS_API perfcat_hook_init(void* args) { return; }
}
