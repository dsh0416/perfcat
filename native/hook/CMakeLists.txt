cmake_minimum_required(VERSION 3.14)

project(perfcat_hook)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PERFCAT_HOOK_SOURCE_FILES
  pch.hpp
  exports.cpp
  hook/hook.hpp
  hook/hook_dxgi.cpp
  hook/hook_dxgi.hpp
  hook/hook_win.cpp
  hook/hook_win.hpp
)

add_library(perfcat_hook SHARED ${PERFCAT_HOOK_SOURCE_FILES})

target_include_directories(perfcat_hook PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
