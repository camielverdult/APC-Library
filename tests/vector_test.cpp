//
// Created by Camiel Verdult on 11/01/2022.
//

#include <gtest/gtest.h>
#include <random>
#include "vector.h"

TEST(vector, creation) {
    // Initialise 2 empty vectors and see what size they have
    mc::vector<int> int_vector{};
    std::vector<int> compare_vector{};

    ASSERT_EQ(int_vector.size(), compare_vector.size()) << "The size of an empty vector is incorrect.";
}

TEST(vector, int_array_compare) {
    // Initialise empty vector
    mc::vector<int> int_vector(1000);

    std::iota(int_vector.begin(), int_vector.begin() + int_vector.capacity(), 0);

    // Initialise int array
    int numbers[1000];

    // Add 1000 elements to both the vector and the int array
    for (std::size_t i = 0; i < 1000; i++) {
        numbers[i] = i;
    }

    // Make sure their content matches
    ASSERT_EQ(*int_vector.raw(), *numbers) << "int array with identical values as vector is different!";
}

TEST(vector, sort) {
    // Initialise empty vector
    mc::vector<int> int_vector{};

    // Initialise int array
    int numbers[1000];

    // Use mersenne twister to generate random numbers, see our previous topic
    // For more information about the working of the mersenne twister
    std::mt19937 mtw;
    mtw.seed((int)time(nullptr));

    // Add 1000 elements to both the vector and the int array
    for (std::size_t i = 0; i < 1000; i++) {
        // Generate random value (we don't want it to be huge)
        uint64_t random_value = mtw() / 100000;

        int_vector.push_back(random_value);
        numbers[i] = random_value;
    }

    std::sort(numbers, &numbers[1000], [](int first, int second) {
        return first > second;
    });

    // Sort our vector by calling .sort()
    int_vector.sort();

    // Make sure the sorted arrays match
    ASSERT_EQ(*int_vector.raw(), *numbers) << "mc::vector sort failed!";
}

TEST(vector, insert) {
    // Initialise empty vector
    mc::vector<int> int_vector{1, 2, 3, 4, 5, 6, 7, 8, 9};

    int_vector.insert(4, 2);

    mc::vector<int> verify_vector{1, 2, 3, 4, 2, 5, 6, 7, 8, 9};

    ASSERT_EQ(int_vector, verify_vector) << "Insert does not insert properly!";
}

TEST(vector, operator_is) {
    mc::vector<int> test{1, 2, 3, 4, 5};
    test.insert(2, 2);

    mc::vector<int> copy{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,24, 25, 26};

    // Test copy operator
    test = copy;

    ASSERT_EQ(test, copy) << "operator= does not work!";
}

TEST(vector, zalewski_idea) {
    struct int_wrapper{
        int value;
        int_wrapper()= default;
        int_wrapper(int v): value{v}{}

        int_wrapper& operator=(int v){
            value = v;
            return *this;
        }

        operator int() const {
            return value;
        }
    };

    mc::vector<int_wrapper> vec{3,6,7,4};

    mc::vector<int> compare{3, 6, 7, 4};

    // int_wrapper and int are different types, compare them by entry instead of by vector template
    for (std::size_t i = 0; i < vec.size(); i++)
        ASSERT_EQ(vec[i], compare[i]) << "int_wrapper vector is not the same as a normal int vector!";
}