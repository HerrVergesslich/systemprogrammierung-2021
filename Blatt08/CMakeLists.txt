cmake_minimum_required(VERSION 3.21)
project(Blatt08)

set(CMAKE_CXX_STANDARD 14)

add_executable(Blatt08 src/smartpointer/RefCounter.cpp include/smartpointer/NullPointerException.h)
include_directories("include")
