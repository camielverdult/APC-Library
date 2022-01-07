//
// Created by Camiel Verdult on 1/7/2022.
//

#ifndef APC_LIBRARY_PAIR_H
#define APC_LIBRARY_PAIR_H

#include <algorithm>
#include <iostream>

// marnix camiel

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

        // Default constructor
        pair(T1 first, T2 second): m_first {first}, m_second {second} {}

        // Copy constructor
        pair(const pair& other): pair{other.first(), other.second()} {}

        // Copy assignment operator
        pair& operator=(pair other) {
            std::swap(m_first, other.first());
            std::swap(m_second, other.second());
            return *this;
        }

        [[maybe_unused]] void print(std::ostream& stream = std::cout) {
            stream << "(" << m_first << ", " << m_second << ")";
        }

        // Getter function for first
        T1 first() {
            return m_first;
        }

        // Getter function for second
        T2 second() {
            return m_second;
        }

        // const getter function for first
        [[maybe_unused]] T1 first() const {
            return m_first;
        }

        // const getter function for second
        [[maybe_unused]] T2 second() const {
            return m_second;
        }

        // Swap function
        [[maybe_unused]] pair& swap(pair other) {
            std::swap(m_first, other.first());
            std::swap(m_second, other.second());
            return *this;
        }

        template <std::size_t I>
        [[maybe_unused]] constexpr T1& get(std::pair<T1, T2>& pair) noexcept {
            if (I == 0) {
                return m_first();
            } else if (I == 1) {
                return m_second();
            }
        }

    private:
        T1 m_first;
        T2 m_second;
    };

    // Out stream operator for pair
    template <typename T1, typename T2>
    std::ostream& operator<<(std::ostream& stream, pair<T1, T2>& other) {
        stream << "(" << other.first() << ", " << other.second() << ")";
        return stream;
    }
};

#endif //APC_LIBRARY_PAIR_H
