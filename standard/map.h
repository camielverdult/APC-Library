//
// Created by Camiel Verdult on 10/01/2022.
//

#ifndef APC_LIBRARY_MAP_H
#define APC_LIBRARY_MAP_H

#include "pair.h"
#include "vector.h"
#include <initializer_list>


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
        using pair_template_pointer = pair_template*;
        using pair_template_reference = pair_template&;
        using pair_template_const_reference = const pair_template&;

        using vector_template = mc::vector<pair_template>;
        using vector_template_pointer = vector_template*;
        using vector_template_reference = vector_template&;
        using vector_template_const_reference = const vector_template&;

        // Default constructor
        [[maybe_unused]] explicit map() : m_vector {} {}

        // initializer list constructor
        explicit map(std::initializer_list<pair_template> list) : map() {
            for (auto& entry : list) {
                push_back(entry);
            }
        };

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

        vector_template_reference raw() {
            /* This function returns the underlying vector */
            return m_vector;
        }

        vector_template_const_reference raw() const {
            /* This function returns the underlying vector */
            return m_vector;
        }


        // Push back function for manual mc::pair<T1, T2>
        [[maybe_unused]] void push_back(const pair_template entry) {
            m_vector.push_back(entry);
        }

        // Push back function for pushing back values of template types
        [[maybe_unused]] void push_back(const first_type first, const second_type second) {
            m_vector.push_back(pair_template(first, second));
        }

        // Insert function for manual mc::pair<T1, T2>
        [[maybe_unused]] void insert(const std::size_t index, const pair_template entry) {
            m_vector.insert(index, entry);
        }

        // Insert function for inserting values of template types
        [[maybe_unused]] void insert(const std::size_t index, const first_type first, const second_type second) {
            m_vector.insert(index, pair_template(first, second));
        }

        [[maybe_unused]] void pop_back() {
            m_vector.pop_back();
        }

        [[maybe_unused]] pair_template_reference at(std::size_t index) {
            return m_vector.at(index);
        }

        [[maybe_unused]] pair_template_reference at(std::size_t index) const {
            return m_vector.at(index);
        }

        [[maybe_unused]] void erase() {
            m_vector.erase();
        }

        [[maybe_unused]] pair_template_reference erase(std::size_t index) {
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

        [[maybe_unused]] void sort() {
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
        [[maybe_unused]] map& operator=(const map other) {
            // The operator= from mc::vector should handle this
            m_vector = other.raw();
            return *this;
        }

        [[maybe_unused]] pair_template_reference operator[](std::size_t index) {
            return m_vector[index];
        }

        [[maybe_unused]] pair_template_const_reference operator[](std::size_t index) const {
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

    template<typename TKey, typename TValue>
    bool operator==(const map<TKey, TValue>& a, const map<TKey, TValue>& b) {
        // Find the lowest index to avoid out of bounds
        if (a.size() != b.size()) {
            return false;
        }

        for (std::size_t i = 0; i < a.size(); i++) {
            // We know that other.size() and m_sz are the same because of the above check
            // bool operator==(const pair<T1, T2>& a, const pair<T1, T2>& b) will handle the check below
            if (a[i] != b[i])
                // Return false if element[i] for both is not identical
                return false;
        }

        // Return if the capacity is the same for both
        return a.capacity() == b.capacity();
    }

}

#endif //APC_LIBRARY_MAP_H
