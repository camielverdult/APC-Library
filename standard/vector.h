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

        vector(std::size_t capacity):
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

        [[maybe_unused]] std::size_t capacity() const {
            return m_cap;
        }

        [[maybe_unused]] std::size_t size() const {
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

        void pop_back() {
            --m_sz;
        }

        T& operator[](std::size_t index){
            return m_data[index];
        }

        const T& operator[](std::size_t index) const{
            return m_data[index];
        }


    private:
        void _adjust_cap() {
            if (m_sz + 1 > m_cap) {
                T* replacement = new T[m_cap + DEFAULT_CAP];

                auto begin = m_data;
                auto end = m_data + m_sz * sizeof(T);

                std::copy(begin, end, replacement);
                m_data = replacement;
                m_cap += DEFAULT_CAP;
            }
        }

        T* m_data;
        std::size_t m_cap;
        std::size_t m_sz;
    };

};

#endif //APC_LIBRARY_VECTOR_H
