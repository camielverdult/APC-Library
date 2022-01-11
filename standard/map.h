//
// Created by Camiel Verdult on 10/01/2022.
//

#ifndef APC_LIBRARY_MAP_H
#define APC_LIBRARY_MAP_H

#include "pair.h"
#include "vector.h"

namespace mc {

    template <typename TKey, typename TValue>
    class map: mc::vector<mc::pair<TKey, TValue>> {
    public:
        map(TKey key, TValue value): m_vector {} {}

        std::size_t capacity() {
            return m_vector.m_cap;
        }

        std::size_t size() {
            return m_vector.m_sz;
        }

        [[maybe_unused]] [[nodiscard]] std::size_t capacity() const {
            return m_vector.m_cap;
        }

        [[maybe_unused]] [[nodiscard]] std::size_t size() const {
            return m_vector.m_sz;
        }

        mc::pair<TKey, TValue>* raw() {
            return m_vector.raw();
        }

        // Copy assignment operator
        map& operator=(map other) {
            std::copy(other.m_vector.raw(), m_vector);
            m_cap = other.capacity();
            m_sz = other.size();

            return *this;
        }

        [[maybe_unused]] void insert(mc::pair<TKey,TValue> entry) {
            m_vector._adjust_cap();
            m_vector.push_back(entry);
        }


    private:
        mc::vector<mc::pair<TKey, TValue>> m_vector;
//        std::size_t m_cap;
//        std::size_t m_sz;

    }

#endif //APC_LIBRARY_MAP_H
