cmake_minimum_required(VERSION 3.21)
project(APC_randomness)

set(CMAKE_CXX_STANDARD 20)

include_directories(examples)

add_executable(std_rand_example examples/std_rand.cpp)

add_executable(linear_congruential_example examples/linear_congruential.cpp)

add_executable(subtract_with_carry_example examples/subtract_with_carry.cpp)

add_executable(gradient_noise_test1 examples/gradient_noise.cpp)

add_executable(mersenne_twister_example examples/mersenne_twister.cpp)