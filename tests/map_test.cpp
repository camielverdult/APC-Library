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
    mc::map<uint64_t, std::string> hash_map;

    // Initialise int array
    uint64_t numbers[1000];

    // Use mersenne twister to generate random numbers, see our previous topic
    // For more information about the working of the mersenne twister
    std::mt19937 mtw;
    mtw.seed((int)time(nullptr));

    // Add 1000 elements to both the vector and the int array
    for (std::size_t i = 0; i < 1000; i++) {
        // Generate random value (we don't want it to be huge)
        uint64_t random_value = mtw() / 100000;

        hash_map.push_back(random_value, "hello friend!");
        numbers[i] = random_value;
    }

    std::sort(numbers, &numbers[1000], [](int first, int second) {
        return first > second;
    });

    // Sort our map by calling .sort()
    hash_map.sort();

    for (std::size_t i = 0; i < 1000; i++) {
        uint64_t value = numbers[i];
        ASSERT_EQ(hash_map[i].first(), value) << "mc::map sort failed!";
        if (hash_map[i].first() != value) {
            break;
        }
    }
}

TEST(map, insert) {
    // Initialise empty map
    mc::map<std::size_t, std::string> hash_map{
        {1, "test1"},
        {2, "test2"},
        {3, "test3"},
        {4, "test4"},
        {5, "test5"},
        {6, "test6"},
        {7, "test7"},
        {8, "test8"},
        {9, "test9"},
        {10, "test10"}
    };

    hash_map.insert(4, 2, "test2");

    mc::vector<int> verify_vector{1, 2, 3, 4, 2, 5, 6, 7, 8, 9, 10};

    for (std::size_t i = 0; i < 10; i++) {
        ASSERT_EQ(hash_map[i].first(), i) << "mc::map insert failed!";
        if (hash_map[i].first() != i) {
            break;
        }
    }
}

TEST(map, operator_is) {
    mc::map<std::size_t, std::string> smol{
            {1, "test1"},
            {2, "test2"},
            {3, "test3"}
    };

    mc::map<std::size_t, std::string> copy{
            {1, "test1"},
            {2, "test2"},
            {3, "test3"},
            {4, "test4"},
            {5, "test5"},
            {6, "test6"},
            {7, "test7"},
            {8, "test8"},
            {9, "test9"},
            {10, "test10"},
            {1, "test1"},
            {2, "test2"},
            {3, "test3"},
            {4, "test4"},
            {5, "test5"},
            {6, "test6"},
            {7, "test7"},
            {8, "test8"},
            {9, "test9"},
            {10, "test10"}
    };

    // Test copy operator
    smol = copy;

    ASSERT_EQ(smol, copy) << "operator= does not work!";
}