//
// Created by Camiel Verdult on 12/01/2022.
//

#include <gtest/gtest.h>

int main(int argc, char** argv) {

    // Initialise gtest (this will also run tests)
    ::testing::InitGoogleTest(&argc, argv);

    // Run all tests
    auto ret_val = RUN_ALL_TESTS();

    return ret_val;
}