//
// Created by Camiel Verdult on 1/7/2022.
//

#include "standard/pair.h"
#include <iostream>

int main() {

    mc::pair ja{"Hallo", 1};

    mc::pair kopie = ja;

    std::cout << kopie;

    return 0;
}