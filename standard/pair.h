//
// Created by Camiel Verdult on 1/7/2022.
//

#ifndef APC_LIBRARY_PAIR_H
#define APC_LIBRARY_PAIR_H

#include <algorithm>

template <typename T1, typename T2>
class pair {

public:
    using first_type = T1;
    using first_pointer = T1*;
    using first_reference = T1&;
    using first_const_reference = const T1&;

    using second_type = T2;
    using second_pointer = T2*;
    using second_reference = T2&;
    using second_const_reference = const T2&;

    pair(T1 first, T2 second): m_first {first}, m_second (second) {}

    ~pair(){
        delete m_first;
        delete m_second;
    }

    pair& operator=(pair other) {
        std::swap(m_first, other.first());
        std::swap(m_second, other.second());
        return *this;
    }

    T1 first() {
        return m_first;
    }

    T2 second() {
        return m_second;
    }

private:
    T1* m_first;
    T2* m_second;
};

#endif //APC_LIBRARY_PAIR_H
