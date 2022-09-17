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
