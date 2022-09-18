cmake_minimum_required(VERSION 3.0)

project(perfcat_hook)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PERFCAT_HOOK_SOURCE_FILES
  pch.hpp
  exports.cpp
)

add_library(perfcat_hook SHARED ${PERFCAT_HOOK_SOURCE_FILES})

target_include_directories(perfcat_hook PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
