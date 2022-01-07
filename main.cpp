//
// Created by Camiel Verdult on 1/7/2022.
//

#include "standard/pair.h"
#include <iostream>
#include <vector>

int main() {

    mc::pair pairOfVectorInt{std::vector<std::string>{"hallo"}, 1};

    mc::pair pairOfInts{1, 1};

    mc::pair pairOfStrings{std::string("Hello"), std::string("World!")};

    std::vector<mc::pair<std::string, int>> people{
        mc::pair<std::string, int>{"Marnix", 20},
        mc::pair<std::string, int>{"Camiel", 20}
    };

    for (auto& person : people) {
        std::cout << person << std::endl;
    }

    // This won't work! The types are different for both first and second
//    pairOfInts.swap(pairOfStrings);

    return 0;
}