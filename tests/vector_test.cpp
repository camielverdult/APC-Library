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
    mc::vector<int> int_vector{1000};

    std::iota(int_vector.begin(), int_vector.end(), 0);

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
    ASSERT_EQ(*int_vector.raw(), *numbers) << "mc::vector sort failed:";
}

TEST(vector, insert) {
    // Initialise empty vector
    mc::vector<int> int_vector{10};

    // std::iota(int_vector.begin(), int_vector.end(), 0);
    // This won't work, because our m_sz variable will not be updated

    for (std::size_t i = 0; i < 10; i++) {
        int_vector.push_back(i);
    }

    int_vector.insert(4, 2);

    int check[] {1, 2, 3, 4, 2, 5, 6, 7, 8, 9};

    ASSERT_EQ(*int_vector.raw(), *check) << "Insert does not insert at the right place!";
}