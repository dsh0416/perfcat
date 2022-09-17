cmake_minimum_required(VERSION 3.0)

project(perfcat_native)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PERFCAT_SOURCE_FILES
  pch.hpp
  injector/installer/installer.hpp
  injector/process/process.hpp
  injector/process/process_win64.hpp
  injector/process/process_win64.cpp
)

add_library(perfcat_native SHARED ${PERFCAT_SOURCE_FILES})

target_include_directories(perfcat_native PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
