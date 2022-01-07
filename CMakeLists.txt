cmake_minimum_required(VERSION 3.21)
project(APC_Library)

set(CMAKE_CXX_STANDARD 20)

include_directories(standard)

add_executable(APC_Library main standard/pair.cpp standard/pair.h)

