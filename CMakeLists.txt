cmake_minimum_required(VERSION 3.21)
project(APC_Library)

set(CMAKE_CXX_STANDARD 20)

include_directories(standard)

# Set options for gnu-like
add_compile_options(-Wall -Wextra -Wpedantic -Werror -fno-omit-frame-pointer -O3)

add_executable(APC_Library main.cpp standard/pair.h standard/vector.h)

