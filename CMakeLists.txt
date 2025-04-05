cmake_minimum_required(VERSION 2.8.4)

project(yuyu-rpc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(deps/googletest)
add_subdirectory(tests)

enable_testing()
