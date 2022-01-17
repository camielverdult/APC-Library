//
// Created by Camiel Verdult on 1/7/2022.
//

#ifndef APC_LIBRARY_PAIR_H
#define APC_LIBRARY_PAIR_H

#include <algorithm>
#include <iostream>

// marnix camiel namespace
namespace mc {

    template <typename T1, typename T2>
    class pair {

    public:
        // It’s a good idea to define those. Others can then easily probe a vector object in generic code.
        using first_type = T1;
        using first_pointer = T1*;
        using first_reference = T1&;
        using first_const_reference = const T1&;

        using second_type = T2;
        using second_pointer = T2*;
        using second_reference = T2&;
        using second_const_reference = const T2&;

        T1 m_first;
        T2 m_second;

        // Default constructor
        pair() = default;

        // Parameterized constructor
        pair(T1 first, T2 second): m_first {first}, m_second {second} {}

        // Copy constructor
        pair(const pair& other): m_first{other.m_first}, m_second{other.m_second} {}

        // Copy assignment operator
        pair& operator=(pair other) {
            m_first = other.m_first;
            m_second = other.m_second;
            return *this;
        }

        // > compare operator
        bool operator>(const pair<T1, T2>& other) const {
            if (m_first == other.m_first) {
                return m_second > other.m_second;
            }
            return m_first > other.m_first;
        }

        // < compare operator
        bool operator<(const pair<T1, T2>& other) const {
            if (m_first == other.m_first) {
                return m_second < other.m_second;
            }
            return m_first < other.m_first;
        }

        // Print function
        [[maybe_unused]] void print(std::ostream& stream = std::cout) {
            stream << "(" << m_first << ", " << m_second << ")";

            // We don't add a newline or std::endl because we might already do that in
            // the call to std::cout << ...
        }

        // Function for swapping the values of two pairs.
        // Only works if the pairs are of the same types.
        void swap(pair& other){
            std::swap(m_first, other.m_first);
            std::swap(m_second, other.m_second);
        }

// Wrong kind of swap:
//        // Function for swapping first and second
//        // This only works if the T1 and T2 are of the same type
//        [[maybe_unused]] pair& swap() {
//            std::swap(m_first, m_second);
//            return *this;
//        }
//
// Pair doesn't need a size function:
//        [[maybe_unused]] std::size_t size() {
//            return sizeof(*this);
//        }
    };

    // Out stream operator for pair
    template <typename T1, typename T2>
    std::ostream& operator<<(std::ostream& stream, pair<T1, T2>& other) {
        other.print();
        return stream;
    }

    template <typename T1, typename T2>
    [[maybe_unused]] pair<T1, T2> make_pair(T1 first, T2 second) {
        return pair{first, second};
    }

    template <typename T1, typename T2>
    bool operator==(const pair<T1, T2>& a, const pair<T1, T2>& b) {
        return (a.first() == b.first() and a.second() == b.second());
    }
}

#endif //APC_LIBRARY_PAIR_H
