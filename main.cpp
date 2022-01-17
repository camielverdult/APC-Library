//
// Created by Camiel Verdult on 1/7/2022.
//

#include "pair.h"
#include "vector.h"
#include "map.h"

#include <iostream>

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

int main() {
    /*
     * Our main function will display functionality in our std::vector and std::pair re-makes
     * Please take a look at the header for all functions, some are not used here
     */

///---------------------------------------------------------------------------------------------------------------------
/// mc::pair
    {
        mc::pair<int_wrapper, int_wrapper> a{};     // sets first and second to 0
        a.first = 1;              // a == (1, 0)
        a.second = 2;             // a == (1, 2)

        mc::pair<int, std::string> b{1, "hello"};   // b == (1, "hello")
        mc::pair<int, std::string> c{b};            // c == (1, "hello")

        auto d = mc::make_pair(1, 2.4);

        std::cout << "a: (" << a.first << ", " << a.second << ")\n";
        std::cout << "b: (" << b.first << ", " << b.second << ")\n";
        std::cout << "c: (" << c.first << ", " << c.second << ")\n";
        std::cout << "d: (" << d.first << ", " << d.second << ")\n";

        mc::pair<int, int> e{1, 2};
        mc::pair<int, int> f{1, 3};
        mc::pair<int, int> g{2, 5};

        std::cout << (e < f) << ", " << (e > g) << ", " << (f > g) << std::endl;

        std::cout << "e" << e << ", f" << f << ", g" << g << std::endl;
    }
///---------------------------------------------------------------------------------------------------------------------
/// mc::vector
    {
        mc::vector<std::string> a{};            // a() empty with capacity 20
        mc::vector<int> b{10};                  // b() empty with capacity 10
        mc::vector<int_wrapper> c{1,2,3,4,5};   // c(1, 2, 3, 4, 5)
        mc::vector<int_wrapper> d{c};           // d(1, 2, 3, 4, 5)


    }


    return 0;
}