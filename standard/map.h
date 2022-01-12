//
// Created by Camiel Verdult on 10/01/2022.
//

#ifndef APC_LIBRARY_MAP_H
#define APC_LIBRARY_MAP_H

#include "pair.h"
#include "vector.h"

namespace mc {

    template<typename TKey, typename TValue>
    class map { // This whole class is a wrapper around an mc::vector<mc::pair>
    public:

        using first_type = TKey;
        using first_pointer = TKey*;
        using first_reference = TKey&;
        using first_const_reference = const TKey&;

        using second_type = TValue;
        using second_pointer = TValue*;
        using second_reference = TValue&;
        using second_const_reference = const TValue&;

        using pair_template = mc::pair<TKey, TValue>;
        using vector_template = mc::vector<pair_template>;

        // Default constructor
        [[maybe_unused]] explicit map() : m_vector {} {}

        // Copy constructor
        map(const map &other) : m_vector {other.raw()} {}

        [[maybe_unused]] std::size_t capacity() {
            /* This function returns the capacity of the underlying vector */
            return m_vector.capacity();
        }

        [[maybe_unused]] std::size_t size() {
            /* This function returns the size of the underlying vector */
            return m_vector.size();
        }

        [[maybe_unused]] [[nodiscard]] std::size_t capacity() const {
            /* This function returns the capacity of the underlying vector as a const */
            return m_vector.capacity();
        }

        [[maybe_unused]] [[nodiscard]] std::size_t size() const {
            /* This function returns the size of the underlying vector as a const */
            return m_vector.size();
        }

        [[maybe_unused]] std::pair<TKey, TValue>* raw() {
            /* This function returns the raw pointer of the underlying vector */
            return m_vector.raw();
        }

        [[maybe_unused]] void push_back(pair_template entry) {
            m_vector.push_back(entry);
        }

        [[maybe_unused]] void insert(pair_template entry) {
            m_vector.insert(entry);
        }

        [[maybe_unused]] void pop_back() {
            m_vector.pop_back();
        }

        [[maybe_unused]] mc::pair<TKey, TValue> &at(std::size_t index) {
            return m_vector.at(index);
        }

        [[maybe_unused]] mc::pair<TKey, TValue> &at(std::size_t index) const {
            return m_vector.at(index);
        }

        [[maybe_unused]] void erase() {
            m_vector.erase(index);
        }

        [[maybe_unused]] mc::pair<TKey, TValue> &&erase(std::size_t index) {
            return m_vector.erase(index);
        }

        // Debug print function
        [[maybe_unused]] void debug_print(std::ostream& stream = std::cout) {
            m_vector.debug_print(stream);
        }

        // Print function
        [[maybe_unused]] void print(std::ostream& stream = std::cout) {
            m_vector.print(stream);
        }

        [[maybe_unused]] vector_template& sort() {
            /*
             * This function will fail if typename T has no operator > function
             */

            return m_vector.sort();
        }

        pair_template* begin() {
            return m_vector.begin();
        }

        pair_template* end() {
            return m_vector.end();
        }

        // Copy assignment operator
        [[maybe_unused]] map &operator=(map other) {
            // The operator= from vector should handle this
            m_vector = other;
        }

        [[maybe_unused]] mc::pair <TKey, TValue> &operator[](std::size_t index) {
            return m_vector[index];
        }

        [[maybe_unused]] const mc::pair<TKey, TValue> &operator[](std::size_t index) const {
            return m_vector[index];
        }

    private:
        vector_template m_vector;
    };

    // Out stream operator for pair
    template<typename TKey, typename TValue>
    std::ostream& operator<<(std::ostream& stream, map<TKey, TValue>& other) {
        other.print(stream);
        return stream;
    }

}

#endif //APC_LIBRARY_MAP_H
