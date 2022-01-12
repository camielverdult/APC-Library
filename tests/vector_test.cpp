//
// Created by Camiel Verdult on 11/01/2022.
//

#include <gtest/gtest.h>
#include "vector.h"

TEST(vector, creation) {
    mc::vector<int> int_vector{};

    int* nothing = {};

    size_t n = sizeof(int)/sizeof(nothing[0]);

    ASSERT_EQ(int_vector.size(), n) << "The size of an empty vector is incorrect.";
}

TEST(vector, push_back) {
    mc::vector<int> int_vector{};

    int numbers[1000];

    for (std::size_t i = 0; i < 1000; i++) {
        int_vector.push_back(i);
        numbers[i] = i;
    }

    ASSERT_EQ(*int_vector.raw(), *numbers);
}