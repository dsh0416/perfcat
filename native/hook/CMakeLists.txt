cmake_minimum_required(VERSION 3.17)

project(perfcat_hook)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)
find_package(CURL REQUIRED)

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

set(PERFCAT_HOOK_INCLUDE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${OPENSSL_INCLUDE_DIRS}
  ${CURL_INCLUDE_DIR}
)

target_include_directories(perfcat_hook PRIVATE ${PERFCAT_HOOK_INCLUDE})

target_link_libraries(perfcat_hook PRIVATE OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(perfcat_hook PRIVATE CURL::libcurl)

if (WIN32)
target_link_libraries(perfcat_hook PRIVATE d3d9 d3d11 d3d12 dxgi)
endif(WIN32)

# Testing
set(PERFCAT_HOOK_SOURCE_TESTS_FILES
  ${PERFCAT_HOOK_SOURCE_FILES}
  tests/main.cpp
)

add_executable(perfcat_hook_tests ${PERFCAT_HOOK_SOURCE_TESTS_FILES})
target_include_directories(perfcat_hook_tests PRIVATE  ${PERFCAT_HOOK_INCLUDE})

enable_testing()
add_test(NAME run_test COMMAND perfcat_hook_tests)
