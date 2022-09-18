#pragma once

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

#ifdef _WIN32

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <Windows.h>

#define DIRECTINPUT_VERSION 0x800
#endif

struct perfcat_hook_init_args {
  const char* work_dir;
  const char* args[32];
  int args_len;
};
using perfcat_hook_init_t = struct perfcat_hook_init_args;
