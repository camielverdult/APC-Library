//
// Created by Camiel Verdult on 1/7/2022.
//

#ifndef APC_LIBRARY_VECTOR_H
#define APC_LIBRARY_VECTOR_H

#include <algorithm>
#include <initializer_list>

namespace mc {

    template <typename T>
    class vector {

    public:
        // It’s a good idea to define those. Others can then easily probe a vector object in generic code.
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;

        // Normal constructor
        explicit vector(std::size_t capacity):
                m_data{ new T[capacity] },
                m_cap{ capacity },
                m_sz{ 0 } {}

        static constexpr std::size_t DEFAULT_CAP{20};

        // Default constructor
        vector(): vector(DEFAULT_CAP) {};

        // Initializer list constructor
        vector(std::initializer_list<T> list) : vector(DEFAULT_CAP) {
            for (auto& entry : list) {
                push_back(entry); // This will update size while pushing back entries
            }
        }

        // Copy constructor
        vector(const vector& other):
            m_data{ new T[other.capacity()] },
            m_cap{ other.capacity() },
            m_sz{ other.size() } {
            // copy over data from other vector

            // use std::uninitialized_copy instead of std::copy because we are dealing with allocated memory
            // thanks to @zaldawid
            std::uninitialized_copy(other.begin(), other.end(), m_data);
        }

        ~vector(){
            // thanks to @zaldawid
            std::destroy_n(m_data, m_sz);
            delete[] m_data;
        }

        [[maybe_unused]] [[nodiscard]] std::size_t capacity() const noexcept {
            return m_cap;
        }

        [[maybe_unused]] [[nodiscard]] std::size_t size() const noexcept {
            return m_sz;
        }

        // Copy assignment operator
        [[maybe_unused]] vector& operator=(const vector& other) {

            // Cppcheck: (warning) operatorEqToSelf: 'operator=' should check for assignment to self to avoid problems with dynamic memory.
            if (this == &other) {
                return *this;
            }

            if (other.capacity() > m_cap) { // using .size() for compare might be a bug
                // We need to delete our previous array because it is too
                // small to fit the other.raw() data and create a new array
                // which will fit the other capacity just fine

                std::destroy_n(m_data, m_sz);
                delete[] m_data;

                m_data = new T[other.capacity()];
            }

            // copy over data from other
            std::copy(other.begin(), other.end(), m_data);

            // Update member variables
            m_cap = other.capacity();
            m_sz = other.size();

            return *this;
        }

        [[maybe_unused]] const_pointer raw() const noexcept {
            return m_data;
        }

        [[maybe_unused]] pointer raw() noexcept {
            return m_data;
        }

        // This cannot be noexcept because you allocate memory which can throw
        // thanks @zaldawid
        void push_back(const_reference entry) {
            adjust_cap();
            m_data[m_sz++] = entry;
//            std::construct_at(m_data[m_sz], entry);
        }

        void push_back(reference& entry) {
            adjust_cap();

            // We use std::move here
            m_data[m_sz++] = std::move(entry);
//            std::construct_at(m_data[m_sz], std::move(entry);
        }

        [[maybe_unused]] void insert(const std::size_t index, const value_type entry) {
            if (m_sz == 0 or index >= m_sz) {
                push_back(entry);
                return;
            }

            adjust_cap();

            // std::copy will not work here for some reason?
            // error: invalid type argument of unary '*' (have 'int')
            for (size_t i = m_sz; i >= index; i--) {
                m_data[i + 1] = m_data[i];
            }

            m_data[index] = entry;
            m_sz++;
        }

        [[maybe_unused]] reference at(std::size_t index) {
            if (index >= m_sz) {
                // Index is out of bounds
                throw "vector_error: at(i) is out of bounds\n";
            }

            return m_data[index];
        }

        [[maybe_unused]] reference at(std::size_t index) const {
            if (index >= m_sz) {
                // Index is out of bounds
                throw "vector_error: at(i) is out of bounds\n";
            }

            return m_data[index];
        }

        [[maybe_unused]] void pop_back() noexcept {
            std::destroy_at(m_data + m_sz - 1); // std::destroy_at calls the destructor of the object pointed to by p, as if by p->~T()
            --m_sz;
        }

        [[maybe_unused]] reference operator[](std::size_t index){
            return m_data[index];
        }

        [[maybe_unused]] const_reference operator[](std::size_t index) const {
            return m_data[index];
        }

        [[maybe_unused]] void erase() {

            // Destroy elements
            std::destroy_n(m_data, m_sz);

            // deallocate
            delete[] m_data;

            // reallocate
            m_data = new T[m_cap];
            m_sz = 0;
        }

        [[maybe_unused]] void erase(std::size_t index) {
            if (index >= m_sz) {
                // Index is out of bounds
                throw "vector_error: erase(i) is out of bounds\n";
            }

            // Shift all data back
//            std::copy(*m_data[index], end(), *m_data[index - 1]);

            for (std::size_t i = index; i < m_sz - 1; i++)
                m_data[i] = m_data[i+1];

            m_sz--;
        }

        // Debug print function
        void debug_print(std::ostream& stream = std::cout) {
            for (std::size_t i = 0; i < m_sz; i++)
                stream << "Index: " << i << " = " << m_data[i];
            // We don't add a newline or std::endl because we might already do that in
            // the call to std::cout << ...
        }

        [[maybe_unused]] void sort() {
            /*
             * This function will fail if typename T has no operator > function
             */

            std::sort(begin(), end(), [](const_reference a, const_reference b){
                return a > b;
            });
        }

        const_pointer begin() const noexcept {
            return m_data;
        }

        const_pointer end() const noexcept {
            // This will point to the last element in our vector
            // To be used in std algorithm functions
            return &m_data[m_sz]; // bug caught by @zaldawid
        }

        pointer begin() noexcept {
            return m_data;
        }

        pointer end() noexcept {
            // This will point to the last element in our vector
            // To be used in std algorithm functions
            return &m_data[m_sz]; // bug caught by @zaldawid
        }

    private:
        static constexpr std::size_t GROWTH_FACTOR{2};
        void adjust_cap(std::size_t how_many_extra_elements = 1) {

            std::size_t required_capacity = m_sz + how_many_extra_elements;

            if (required_capacity > m_cap) {
                std::size_t new_capacity = m_cap;

                // Calculate new capacity
                while (new_capacity <= required_capacity)
                    new_capacity *= GROWTH_FACTOR;

                //
                pointer replacement = new T[new_capacity];

                // Move over contents of array to replacement
                std::uninitialized_move(begin(), end(), replacement);

                // Destroy left over elements
                std::destroy_n(m_data, m_sz);

                // Delete old memory
                delete[] m_data;

                m_data = replacement;
                m_cap = new_capacity;
            }
        }

        pointer m_data;
        std::size_t m_cap;
        std::size_t m_sz;
    };

    // Out stream operator for vector
    template <typename T>
    std::ostream& operator<<(std::ostream& stream, vector<T>& other) {

        stream << "vector{";

        for (std::size_t i = 0; i < other.size(); i++) {
            stream << other[i];
            // Add ', ' between every element except the last
            if (i != other.size() - 1)
                stream << ", ";
        }

        stream << "}";

        return stream;
    }

    // The inequality operator is automatically generated by the compiler if operator== is defined. (Since C++20)
    // See https://en.cppreference.com/w/cpp/language/operators
    template <typename T>
    bool operator==(const vector<T>& a, const vector<T>& b) {
        // Find the lowest index to avoid out of bounds
        if (a.size() != b.size()) {
            return false;
        }

        for (std::size_t i = 0; i < a.size(); i++) {
            // We know that other.size() and m_sz are the same because of the above check
            if (a[i] != b[i])
                // Return false if element[i] for both is not identical
                return false;
        }

        // Return if the capacity is the same for both
        return a.capacity() == b.capacity();
    }

}

#endif //APC_LIBRARY_VECTOR_H
