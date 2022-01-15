//
// Created by Camiel Verdult on 12/01/2022.
//

#include <gtest/gtest.h>
#include "map.h"
#include <random>

TEST(map, creation) {
    // Initialise 2 empty vectors and see what size they have
    mc::map<std::size_t, std::string> int_map{};
    std::map<std::size_t, std::string> compare_map{};

    ASSERT_EQ(int_map.size(), compare_map.size()) << "The size of an empty map is incorrect.";
}

TEST(map, int_array_compare) {
    // Initialise empty vector
    mc::map<std::size_t, std::string> hash_map;

    // Add 1000 elements to both the vector and the int array
    for (std::size_t i = 0; i < 1000; i++) {
        hash_map.push_back(i, "test");
    }

    for (std::size_t i = 0; i < 1000; i++) {
        ASSERT_EQ(hash_map[i].first(), i) << "map is broken";
        if (hash_map[i].first() != i) {
            break;
        }
    }
}

TEST(map, sort) {
    // Initialise empty vector
    mc::map<std::size_t, std::string> hash_map;

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

        hash_map.push_back(random_value, "test");
        numbers[i] = random_value;
    }

    std::sort(numbers, &numbers[1000], [](int first, int second) {
        return first > second;
    });

    // Sort our map by calling .sort()
    hash_map.sort();

    for (std::size_t i = 0; i < 1000; i++) {
        ASSERT_EQ(hash_map[i].first(), i) << "mc::map sort failed!";
        if (hash_map[i].first() != i) {
            break;
        }
    }
}

TEST(map, insert) {
    // Initialise empty vector
    mc::vector<int> int_vector{1, 2, 3, 4, 5, 6, 7, 8, 9};

    int_vector.insert(4, 2);

    mc::vector<int> verify_vector{1, 2, 3, 4, 2, 5, 6, 7, 8, 9};

    ASSERT_EQ(int_vector, verify_vector) << "Insert does not insert properly!";
}

TEST(map, operator_is) {
    mc::vector<int> test{1, 2, 3, 4, 5};
    test.insert(2, 2);

    mc::vector<int> copy{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,24, 25, 26};

    // Test copy operator
    test = copy;

    ASSERT_EQ(test, copy) << "operator= does not work!";
}