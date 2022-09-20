#pragma once

#include <array>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <mutex>
#include <string>
#include <unordered_map>
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

namespace perfcat {
struct perfcat_hook_init_args {
  uint64_t wake_up_tid;
};
using perfcat_hook_init_t = struct perfcat_hook_init_args;
} // namespace perfcat
