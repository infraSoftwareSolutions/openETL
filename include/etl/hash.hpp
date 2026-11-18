#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <vector>
#include "warning.hpp"

#pragma once
#ifndef ETL___ENCRYPTION_HPP
#define ETL___ENCRYPTION_HPP
namespace etl
{
    /**
     * @brief Associates strings with sequential 8-bit values.
     *
     * Values are assigned in insertion order, beginning at zero. The map
     * contains one entry per distinct string; adding an existing string
     * replaces its value.
     */
    class hash_enum {
        private:
        ocf::u8 counter = 0;
        ocf::hash_map<ocf::str, ocf::u8> objectMap;

        public:
        /** @brief Constructs an empty string-to-value map. */
        hash_enum() = default;

        /** @brief Destroys the map. */
        ~hash_enum() = default;

        /**
         * @brief Constructs a map from a list of strings.
         * @param list Strings to insert in order.
         */
        hash_enum(const ocf::initList<ocf::str> &list) noexcept {
            for(const ocf::str &element : list) {
                objectMap[element] = counter;
                counter++;
            }
        }

        /**
         * @brief Copies the source map.
         * @param other Map to copy.
         * @note The counter is default-initialized rather than copied by this
         * constructor.
         */
        hash_enum(const hash_enum& other) noexcept : objectMap(other.objectMap) {}

        /**
         * @brief Adds a string and assigns the next counter value.
         * @param enum_val String to associate with a value.
         * @warning When the 8-bit counter reaches UINT8_MAX, an error is
         * printed, but insertion and counter increment still proceed.
         */
        constexpr inline void add(const ocf::str& enum_val) noexcept {
            if(counter == UINT8_MAX) {
                std::cerr << "out of limit issue: can't add to full enum hast map.\n";
            }
            objectMap[enum_val] = counter;
            counter++;
        }

        /**
         * @brief Gets the number of distinct strings in the map.
         * @return Number of distinct keys.
         */
        constexpr inline size_t size() noexcept {
            return objectMap.size();
        }

        /**
         * @brief Gets an iterator to the beginning of the underlying map.
         * @return Iterator to the first map entry.
         */
        inline auto begin() noexcept {
            return objectMap.begin();
        }

        /**
         * @brief Gets an iterator to the end of the underlying map.
         * @return Iterator to the position after the last map entry.
         */
        inline auto end() noexcept {
            return objectMap.end();
        }

        /**
         * @brief Inserts a string using the next counter value.
         * @param enum_val String to insert.
         */
        constexpr inline void operator<<(const ocf::str& enum_val) noexcept { add(enum_val); }
        
        /**
         * @brief Looks up the value associated with a string.
         * @param enum_val String to look up.
         * @return The mapped 8-bit value.
         * @warning A missing string causes the underlying at() call to fail;
         * because this operator is noexcept, such a failure terminates the
         * process.
         */
        constexpr inline ocf::u8 operator[](const ocf::str& enum_val) noexcept { return objectMap.at(enum_val); }

        /**
         * @brief Replaces this map and counter with the source contents.
         * @param other Map to copy.
         */
        inline void operator=(const hash_enum& other) noexcept {
            counter = other.counter;
            objectMap = other.objectMap;
        }
    };

    /**
     * @brief Stores indexed flags in a byte vector.
     *
     * Bit positions are addressed by 16-bit unsigned values. Insertion sets a
     * bit, indexing reads it, and the right-shift operator reads and clears it.
     */
    class hash_bit {
        private:
        ocf::vec<ocf::u8> vector_bytes;
        const size_t maxSize = (size_t)(UINT16_MAX / 8);
        protected:
        void allocate_to(const ocf::u16& value) {
            if(value < vector_bytes.size() / 8) return;
            if(vector_bytes.size() >= maxSize - 1) return;
            for(ocf::u16 i = 0; i < value - vector_bytes.size() / 8; i++) vector_bytes.push_back(0);
        }
        public:
        /** @brief Constructs an empty bit set. */
        hash_bit() = default;

        /** @brief Destroys the bit set. */
        ~hash_bit() = default;

        /**
         * @brief Constructs a bit set by copying its backing bytes.
         * @param values Bytes to copy into the bit set.
         */
        hash_bit(const ocf::vec<ocf::u8>& values) : vector_bytes(values) {}

        /**
         * @brief Constructs a bit set from an initializer list of bytes.
         * @param list Bytes to copy into the bit set.
         */
        hash_bit(const ocf::initList<ocf::u8> &list) : vector_bytes(list) {}

        /**
         * @brief Copies another bit set's backing bytes.
         * @param other Bit set to copy.
         */
        hash_bit(const hash_bit& other) : vector_bytes(other.vector_bytes) {}
    
        /**
         * @brief Sets the bit at the given position.
         * @param value Bit position to set.
         * @note Values at or above the implementation's maxSize are ignored.
         * @warning Setting position zero on an empty instance does not
         * allocate a backing byte before indexing it.
         */
        inline void operator<<(const ocf::u16& value) noexcept {
            if(value >= maxSize) return;
            allocate_to(value);
            vector_bytes[value/8] |= (1U << value % 8);
        }

        /**
         * @brief Reads the bit at the given position.
         * @param value Bit position to read.
         * @return Whether the selected bit is set.
         * @warning The current bounds check may still access outside the
         * backing vector for some out-of-range values.
         */
        constexpr bool operator[](const ocf::u16& value) {
            if(value >= maxSize && value >= vector_bytes.size()) return false;
            return (vector_bytes[value/8] >> (value % 8)) & 1;
        }

        /**
         * @brief Reads and clears the bit at the given position.
         * @param value Bit position to read and clear.
         * @return The bit's previous value.
         * @warning The current bounds check may still access outside the
         * backing vector for some out-of-range values.
         */
        constexpr bool operator>>(const ocf::u16& value) {
            if(value >= maxSize && value >= vector_bytes.size()) return false;
            bool result = (vector_bytes[value/8] >> (value % 8)) & 1;
            vector_bytes[value/8] &= ~(1U << value % 8);
            return result;
        }

        /**
         * @brief Replaces this bit set's backing bytes with another's.
         * @param other Bit set to copy.
         */
        inline void operator=(const hash_bit& other) {
            vector_bytes = other.vector_bytes;
        }
    };
}

#endif // ETL___ENCRYPTION_HPP