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
        vector& operator=(map other) {
            std::copy(other.raw(), m_data);
            m_cap = other.capacity();
            m_sz = other.size();

            return *this;
        }

private:
    mc::vector<mc::pair<TKey, TValue>> m_vector;
}

#endif //APC_LIBRARY_MAP_H
