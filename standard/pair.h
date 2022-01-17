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

        T1 first;
        T2 second;

        // Default constructor
        // dza: You assume that T1 and T2 can be default-constructed - this is very often not the case
        // We use it anyway
        pair() = default;

        // Parameterized constructor
        pair(T1 first, T2 second): first {std::move(first)}, second {std::move(second)} {}

        // Copy constructor
        pair(const pair& other): first{other.first}, second{other.second} {}

        // Copy assignment operator
        pair& operator=(pair other) {
            first = other.first;
            second = other.second;
            return *this;
        }

        // > compare operator
        bool operator>(const pair<T1, T2>& other) const {
            if (first == other.first) {
                return second > other.second;
            }
            return first > other.first;
        }

        // < compare operator
        bool operator<(const pair<T1, T2>& other) const {
            if (first == other.first) {
                return second < other.second;
            }
            return first < other.first;
        }

        void swap(){
            // see https://stackoverflow.com/questions/6380862/how-to-provide-a-swap-function-for-my-class
            using std::swap; // enable 'std::swap' to be found
            swap(first, second);
        }
    };

    // Out stream operator for pair
    template <typename T1, typename T2>
    std::ostream& operator<<(std::ostream& stream, pair<T1, T2>& other) {
        stream << "(" << other.first << ", " << other.second << ")";
        return stream;
    }

    template <typename T1, typename T2>
    [[maybe_unused]] pair<T1, T2> make_pair(T1 first, T2 second) {
        return pair{first, second};
    }

    // The inequality operator is automatically generated by the compiler if operator== is defined. (Since C++20)
    // See https://en.cppreference.com/w/cpp/language/operators
    template <typename T1, typename T2>
    bool operator==(const pair<T1, T2>& a, const pair<T1, T2>& b) {
        return (a.first == b.first and a.second == b.second);
    }
}

#endif //APC_LIBRARY_PAIR_H
