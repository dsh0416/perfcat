cmake_minimum_required(VERSION 3.17)

project(perfcat_native)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(hook)
add_subdirectory(injector)

enable_testing()
add_test(NAME perfcat_hook_tests COMMAND perfcat_hook_tests)
