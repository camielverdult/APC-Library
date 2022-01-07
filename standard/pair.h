//
// Created by Camiel Verdult on 1/7/2022.
//

#ifndef APC_LIBRARY_PAIR_H
#define APC_LIBRARY_PAIR_H

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

private:
    T1* m_first;
    T2* m_second;
};

#endif //APC_LIBRARY_PAIR_H
