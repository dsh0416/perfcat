cmake_minimum_required(VERSION 3.17)

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

# openssl
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIRS})
target_link_libraries(perfcat_hook PRIVATE OpenSSL::SSL OpenSSL::Crypto)

# curl
find_package(CURL CONFIG REQUIRED)
include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(perfcat_hook PRIVATE CURL::libcurl)

if (WIN32)
target_link_libraries(perfcat_hook PRIVATE d3d9 d3d11 d3d12 dxgi)
endif(WIN32)
