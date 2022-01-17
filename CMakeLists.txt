cmake_minimum_required(VERSION 3.12)
project(APC-Library)

set(CMAKE_CXX_STANDARD 20)

set(target_main APC-Library)

include_directories(standard)

# Set options for gnu-like
add_compile_options(-Wall -Wextra -Wpedantic -Werror -fno-omit-frame-pointer )

# Setup our main executable
add_executable(
        ${target_main}
        main.cpp
        standard/pair.h
        standard/vector.h
        standard/map.h
        "std headers/GNU_pair.h" "std headers/GNU_vector.h" "std headers/GNU_map.h")

# How to add gtest to your CMakeLists.txt:
# https://github.com/google/googletest/tree/main/googletest#incorporating-into-an-existing-cmake-project

# Download gtest
include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)

# for Windows: prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# Setup our testing executable
set(tests_target mc_lib_tests)

add_executable(
        # Executable name, set above
        ${tests_target}

        # This runs the tests
        tests/test_runner.cpp

        # Test for mc::vector
        tests/vector_test.cpp
        standard/vector.h

        # Test for mc::pair
        tests/pair_test.cpp
        standard/pair.h

        # Test for mc::map
        tests/map_test.cpp
        standard/map.h
)

# Link our test executable code with gtest
target_link_libraries(${tests_target} gtest_main)
