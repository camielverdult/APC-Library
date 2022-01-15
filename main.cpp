//
// Created by Camiel Verdult on 1/7/2022.
//

#include "pair.h"
#include "vector.h"
#include "map.h"

#include <iostream>

int main() {
    /*
     * Our main function will display functionality in our std::vector and std::pair re-makes
     * Please take a look at the header for all functions, some are not used here
     */

//    mc::map<std::string, uint64_t> values;
//
//    values.push_back(mc::pair<std::string, uint64_t>{"Hi", 1});
//    std::cout << values << "\n";
//
//    mc::vector<int> test{1, 2, 3, 4};
//
//    test.insert(0, 0);
//
//    return 0;
//
//    mc::pair pairOfVectorInt{std::vector<std::string>{"hallo"}, 1};
//
//    mc::pair pairOfInts{1, 2};
//
//    mc::pair pairOfStrings{std::string("Hello"), std::string("World!")};
//
//    std::vector<mc::pair<std::string, int>> people{
//        mc::pair<std::string, int>{"Marnix", 20},
//        mc::pair<std::string, int>{"Camiel", 20}
//    };
//
//    std::cout << "People: " << std::endl;
//
//    for (auto& person : people) {
//        std::cout << person << std::endl;
//    }
//
//    // This won't work! The types are different for both first and second
//    // pairOfInts.swap();
//
//    // This will work fine on the other hand
//    std::cout << "Swap print: " << mc::pair<int, int>{1, 20}.swap() << std::endl;
//
//    // Test our vector!
//    mc::vector<std::string> vec{};
//    vec.push_back("Hello");
//    vec.push_back("Alice.");
//    vec.push_back("How");
//    vec.push_back("are");
//    vec.push_back("you");
//    vec.push_back("today?");
//
//    std::cout << "Vector print: " << vec << std::endl;
//
//    mc::pair<std::string, int> marnix{"Marnix", 20};
//    mc::pair<std::string, int> camiel{"Camiel", 20};
//
//    mc::pair<int, std::string> setie;
//
//    mc::pair<std::string, int> pairArray[10];
//
//    pairArray[1] = camiel;
//
//    std::cout << pairArray[1] << std::endl;
//
//    mc::vector<mc::pair<std::string, int>> set;
//
//    set.push_back(mc::pair<std::string, int>{"One", 1});
//    set.push_back(mc::pair<std::string, int>{"Two", 2});
//
//    // Delete the second pair out of our vector
//    set.erase(1);
//    std::cout << set << std::endl;
//
//    // Fill an array with random numbers and sort them
//    mc::vector<uint32_t> unsorted;
//
//    // Use mersenne twister to generate random numbers, see our previous topic
//    // For more information about the working of the mersenne twister
//    std::mt19937 mtw;
//    mtw.seed((int)time(nullptr));
//
//    int iterations = 100000;
//
//    std::cout << "Iterations: " << iterations << std::endl;
//
//    for (int i = 0; i < iterations; i++) {
//        unsorted.push_back(mtw());
//    }
//
//    auto start = std::chrono::high_resolution_clock::now();
//
//    unsorted.sort();
//
//    auto finish = std::chrono::high_resolution_clock::now();
//    std::cout << "Sorted " << unsorted.size() << " elements in " << std::chrono::duration_cast<std::chrono::milliseconds>(finish-start).count() << " ms\n";
//
//    return 0;


    return 0;
}