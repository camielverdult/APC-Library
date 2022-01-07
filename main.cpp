//
// Created by Camiel Verdult on 1/7/2022.
//

#include "standard/pair.h"
#include <iostream>

int main() {

    pair ja{"Hallo", 1};

    pair kopie = ja;

    std::cout << kopie;

    return 0;
}