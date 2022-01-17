//
// Created by Camiel Verdult on 12/01/2022.
//

#include <gtest/gtest.h>
#include "pair.h"

TEST(pair, creation) {
    // Initialise 2 pairs and test if they are equal
    mc::pair<int, int> int_map{1, 2};
    mc::pair<int, int> compare_map{1, 2};

    ASSERT_EQ(int_map, compare_map) << "The content of the pairs is not the same.";
}

TEST(pair, compare) {
    // Initialise 2 pairs and test if they are equal
    mc::pair<int, int> int_map{1, 2};
    mc::pair<int, int> compare_pair{3, 4};

    ASSERT_FALSE(int_map == compare_pair) << "Compare ==operator of pair is broken!";
    ASSERT_FALSE(int_map > compare_pair) << "Compare >operator of pair is broken!";
    ASSERT_TRUE(int_map < compare_pair) << "Compare <operator of pair is broken!";
    ASSERT_EQ(compare_pair, mc::make_pair(3, 4));

}