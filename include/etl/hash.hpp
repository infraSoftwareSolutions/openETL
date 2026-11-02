#include <cstdint>
#include <iostream>
#include "cfrost/types.h"
#include "warning.hpp"

#pragma once
#ifndef ETL___ENCRYPTION_HPP
#define ETL___ENCRYPTION_HPP
namespace etl
{
    class hash_enum {
        private:
        uint8_t counter = 0;
        ocf::hash_map<ocf::str, uint8_t> objectMap;

        public:
        hash_enum() = default;
        ~hash_enum() = default;

        hash_enum(const ocf::initList<ocf::str> &list) noexcept {
            for(ocf::str element : list) {
                objectMap[element] = counter;
                counter++;
            }
        }

        hash_enum(const hash_enum& other) noexcept : objectMap(other.objectMap) {}

        constexpr inline void add(const ocf::str& enum_val) noexcept {
            if(counter == UINT8_MAX) {
                std::cerr << "out of limit issue: can't add to full enum hast map.\n";
            }
            objectMap[enum_val] = counter;
            counter++;
        }

        constexpr inline size_t size() noexcept {
            return objectMap.size();
        }

        inline auto begin() noexcept {
            return objectMap.begin();
        }

        inline auto end() noexcept {
            return objectMap.end();
        }

        constexpr inline void operator<<(const ocf::str& enum_val) noexcept { add(enum_val); }
        
        constexpr inline uint8_t operator[](const ocf::str& enum_val) noexcept { return objectMap.at(enum_val); }

        inline void operator=(const hash_enum& other) noexcept {
            counter = other.counter;
            objectMap = other.objectMap;
        }
    };

    class hash_bit {
        private:
        ocf::vec<uint8_t> vector_bytes;
        const size_t maxSize = (size_t)(UINT16_MAX / 8);
        protected:
        void allocate_to(const uint16_t& value) {
            if(value < vector_bytes.size() / 8) return;
            if(vector_bytes.size() >= maxSize - 1) return;
            for(uint16_t i = 0; i < value - vector_bytes.size() / 8; i++) vector_bytes.push_back(0);
        }
        public:
        hash_bit() = default;
        ~hash_bit() = default;

        hash_bit(const ocf::vec<uint8_t>& values) : vector_bytes(values) {}
        hash_bit(ocf::initList<uint8_t> values) : vector_bytes(values) {}
        hash_bit(const hash_bit& other) : vector_bytes(other.vector_bytes) {}
    
        inline void operator<<(const uint16_t& value) noexcept {
            if(value >= maxSize) return;
            allocate_to(value);
            vector_bytes[value/8] |= (1U << value % 8);
        }

        constexpr bool operator[](const uint16_t& value) {
            if(value >= maxSize && value >= vector_bytes.size()) return false;
            return (vector_bytes[value/8] >> (value % 8)) & 1;
        }

        constexpr bool operator>>(const uint16_t& value) {
            if(value >= maxSize && value >= vector_bytes.size()) return false;
            bool result = (vector_bytes[value/8] >> (value % 8)) & 1;
            vector_bytes[value/8] &= ~(1U << value % 8);
            return result;
        }

        inline void operator=(const hash_bit& other) {
            vector_bytes = other.vector_bytes;
        }
    };
}

#endif // ETL___ENCRYPTION_HPP