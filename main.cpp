//
// Created by Camiel Verdult on 1/7/2022.
//

#include "standard/pair.h"
#include <iostream>
#include <vector>
#include "standard/vector.h"

int main() {

    mc::pair pairOfVectorInt{std::vector<std::string>{"hallo"}, 1};

    mc::pair pairOfInts{1, 2};

    mc::pair pairOfStrings{std::string("Hello"), std::string("World!")};

    std::vector<mc::pair<std::string, int>> people{
        mc::pair<std::string, int>{"Marnix", 20},
        mc::pair<std::string, int>{"Camiel", 20}
    };

    for (auto& person : people) {
        std::cout << person << std::endl;
    }

    // This won't work! The types are different for both first and second
    // pairOfInts.swap();

    // Test our vector!
    mc::vector<std::string> vec{};
    vec.push_back("Hello");
    vec.push_back("Alice.");
    vec.push_back("How");
    vec.push_back("are");
    vec.push_back("you");
    vec.push_back("today?");

    for (std::size_t i=0; i < vec.size(); ++i){
        std::cout << vec[i] << ' ';
    }

    mc::vector<mc::pair<std::string, int>> set;



    return 0;
}