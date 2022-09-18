cmake_minimum_required(VERSION 3.17)

project(perfcat_injector)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PERFCAT_NATIVE_SOURCE_FILES
  pch.hpp
  exports.cpp
  installer/installer.hpp
  installer/installer_win.cpp
  installer/installer_win.hpp
  process/process.hpp
  process/process_win.cpp
  process/process_win.hpp
)

add_library(perfcat_native SHARED ${PERFCAT_NATIVE_SOURCE_FILES})

target_include_directories(perfcat_native PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
