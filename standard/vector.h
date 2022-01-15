//
// Created by Camiel Verdult on 1/7/2022.
//

#ifndef APC_LIBRARY_VECTOR_H
#define APC_LIBRARY_VECTOR_H

#include <algorithm>
#include <initializer_list>

#define DEFAULT_CAP 20

namespace mc {

    template <typename T>
    class vector {

    public:
        // It’s a good idea to define those. Others can then easily probe a vector object in generic code.
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using const_reference = const T&;

        explicit vector(std::size_t capacity):
                m_data{ new T[capacity]},
                m_cap{ capacity },
                m_sz{ 0 } {}

        vector(): vector(DEFAULT_CAP) {};

        explicit vector(std::initializer_list<T> list) : vector(DEFAULT_CAP) {
            for (auto& entry : list) {
                push_back(entry);
            }
        };

        // Copy constructor
        vector(const vector& other): m_data{ new T[other.capacity()]},
                                     m_cap{ other.size() },
                                     m_sz{ 0 } {}

        ~vector(){
            delete[] m_data;
        }

        [[maybe_unused]] [[nodiscard]] std::size_t capacity() const noexcept {
            return m_cap;
        }

        [[maybe_unused]] [[nodiscard]] std::size_t size() const noexcept {
            return m_sz;
        }

        bool operator==(const vector& other) {
            // Find the lowest index to avoid out of bounds
            if (other.size() != m_sz) {
                return false;
            }

            for (std::size_t i = 0; i < m_sz; i++) {
                // We know that other.size() and m_sz are the same because of the above check
                if (other.raw()[i] != m_data[i])
                    // Return false if element[i] for both is not identical
                    return false;
            }

            // Return if the capacity is the same for both
            return m_cap == other.capacity();
        }

        // Copy assignment operator
        [[maybe_unused]] vector& operator=(const vector& other) {

            // Cppcheck: (warning) operatorEqToSelf: 'operator=' should check for assignment to self to avoid problems with dynamic memory.
            if (other == *this) {
                return *this;
            }

            if (other.size() > m_cap) {
                // We need to delete our previous array because it is too
                // small to fit the other.raw() data and create a new array
                // which will fit the other capacity just fine

                delete[] m_data;
                m_data = new T[other.capacity()];

            }

            // copy over data from other
            std::copy(other.begin(), other.end(), m_data);

            m_cap = other.capacity();
            m_sz = other.size();

            return *this;
        }

        [[maybe_unused]] T* raw() const noexcept {
            return m_data;
        }

        [[maybe_unused]] void push_back(value_type entry) {
            _adjust_cap();
            m_data[m_sz++] = entry;
        }

        [[maybe_unused]] void insert(const std::size_t index, const value_type entry) {
            if (m_sz == 0 or index >= m_sz) {
                push_back(entry);
                return;
            }

            _adjust_cap();

            // std::copy will not work here for some reason?
            // error: invalid type argument of unary '*' (have 'int')
//            std::copy(*m_data[index], end(), *m_data[index + 1]);
            for (size_t i = m_sz; i > index; i--) {
                m_data[i + 1] = m_data[i];
            }

            m_data[m_sz++] = entry;
        }

        [[maybe_unused]] reference at(std::size_t index) {
            if (index >= m_sz) {
                // Index is out of bounds
                return nullptr;
            }

            return m_data[index];
        }

        [[maybe_unused]] reference at(std::size_t index) const {
            if (index >= m_sz) {
                // Index is out of bounds
                return nullptr;
            }

            return m_data[index];
        }

        [[maybe_unused]] void pop_back() noexcept {
            --m_sz;
        }

        [[maybe_unused]] reference operator[](std::size_t index){
            return this->at(index);
        }

        [[maybe_unused]] const_reference operator[](std::size_t index) const {
            return this->at(index);
        }

        [[maybe_unused]] void erase() {
            // Clear out m_data
            delete[] m_data;
            m_data = new T[m_cap];
            m_sz = 0;
        }

        [[maybe_unused]] void erase(std::size_t index) {
            if (index >= m_sz) {
                // Index is out of bounds
                return;
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

        // Print function
        void print(std::ostream& stream = std::cout) {
            for (std::size_t i = 0; i < m_sz; i++) {
                stream << m_data[i];
                if (i != m_sz - 1)
                    stream << " ";
            }
            // We don't add a newline or std::endl because we might already do that in
            // the call to std::cout << ...
        }

        [[maybe_unused]] void sort() {
            /*
             * This function will fail if typename T has no operator > function
             */

            std::sort(begin(), end(), [](reference a, reference b){
                return a > b;
            });
        }

        T* begin() const noexcept {
            return m_data;
        }

        T* end() const noexcept {
            // This will point to the last element in our vector
            // To be used in std algorithm functions
            return &m_data[m_cap];
        }

    private:
        void _adjust_cap() {
            if (m_sz + 1 > m_cap) {
                T* replacement = new T[m_cap + DEFAULT_CAP];

                std::copy(begin(), end(), replacement);
                m_data = replacement;
                m_cap += DEFAULT_CAP;
            }
        }

        T* m_data;
        std::size_t m_cap;
        std::size_t m_sz;
    };

    // Out stream operator for pair
    template <typename T>
    std::ostream& operator<<(std::ostream& stream, vector<T>& other) {
        other.print();
        return stream;
    }

}

#endif //APC_LIBRARY_VECTOR_H
