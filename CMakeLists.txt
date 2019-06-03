cmake_minimum_required (VERSION 3.7)

project (cpptools)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_CXX_FLAGS -pthread)  # for ThreadPool.h in linux

add_executable (example main.cpp ThreadPool.h timer.h parallel_for.h pystring.h pystring.cpp)