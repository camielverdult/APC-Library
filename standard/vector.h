//
// Created by Camiel Verdult on 1/7/2022.
//

#ifndef APC_LIBRARY_VECTOR_H
#define APC_LIBRARY_VECTOR_H

#include <algorithm>

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

        // Copy constructor
        vector(const vector& other): m_data{ new T[other.capacity()]},
                                     m_cap{ other.size() },
                                     m_sz{ 0 } {}

        ~vector(){
            delete[] m_data;
        }

        std::size_t capacity() {
            return m_cap;
        }

        std::size_t size() {
            return m_sz;
        }

        [[maybe_unused]] [[nodiscard]] std::size_t capacity() const {
            return m_cap;
        }

        [[maybe_unused]] [[nodiscard]] std::size_t size() const {
            return m_sz;
        }

        // Copy assignment operator
        vector& operator=(vector other) {
            std::copy(other.raw(), m_data);
            m_cap = other.capacity();
            m_sz = other.size();

            return *this;
        }

        T* raw() {
            return m_data;
        }

        [[maybe_unused]] void push_back(T entry) {
            _adjust_cap();
            m_data[m_sz++] = entry;
        }

        [[maybe_unused]] T* at(std::size_t index) {
            if (index >= m_sz) {
                return nullptr;
            }

            return m_data[index];
        }

        [[maybe_unused]] void pop_back() {
            --m_sz;
        }

        T& operator[](std::size_t index){
            return m_data[index];
        }

        const T& operator[](std::size_t index) const{
            return m_data[index];
        }

        [[maybe_unused]] void erase() {
            // Clear out m_data
            delete[] m_data;
            m_data = new T[m_cap];
            m_sz = 0;
        }

        [[maybe_unused]] vector& erase(std::size_t index) {
            if (index >= m_sz) {
                // Index is out of bounds, return empty vector
                std::cout << "ERROR: index passed to vector.erase() out of bounds \n";
                return *this;
            }

            // Shift all data back
            for (std::size_t i = index; i < m_sz - 1; i++)
                m_data[i] = m_data[i+1];

            m_sz--;

            return *this;
        }

        // Print function
        [[maybe_unused]] void debug_print(std::ostream& stream = std::cout) {
            for (std::size_t i = 0; i < m_sz; i++)
                stream << "Index: " << i << " = " << m_data[i];
            // We don't add a newline or std::endl because we might already do that in
            // the call to std::cout << ...
        }

        // Print function
        [[maybe_unused]] void print(std::ostream& stream = std::cout) {
            for (std::size_t i = 0; i < m_sz; i++) {
                stream << m_data[i];
                if (i != m_sz - 1)
                    stream << " ";
            }
            // We don't add a newline or std::endl because we might already do that in
            // the call to std::cout << ...
        }

        [[maybe_unused]] vector& sort() {
            /*
             * This function will fail if typename T has no operator > function
             */

            std::sort(begin(), end(), [](T& a, T& b){
                return a > b;
            });

            return *this;
        }

        T* begin() {
            return m_data;
        }

        T* end() {
            return &m_data[m_sz];
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

};

#endif //APC_LIBRARY_VECTOR_H
