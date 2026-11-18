#include "function.hpp"
#include "io.hpp"
#include "cformat/types.h"

#pragma once
#ifndef ETL___ENUM_HPP
#define ETL___ENUM_HPP

namespace etl
{
    /**
     * @brief Counts occurrences of decimal digit characters.
     *
     * Digit counts are accumulated when characters or strings are inserted.
     * Non-digit input passed to the character insertion operator is reported
     * through the ETL error output.
     */
    class enum_decimal
    {
    private:
        ocf::vec<size_t> hash_numbers;

    protected:
        /** @brief Initializes a zero count for each decimal digit. */
        void allocate_numbers()
        {
            for (char c = '0'; c <= '9'; c++)
                hash_numbers.push_back(0);
        }

    public:
        /** @brief Constructs a digit counter with all counts initialized to zero. */
        enum_decimal() { allocate_numbers(); }

        /** @brief Destroys the digit counter. */
        ~enum_decimal() = default;

        /**
         * @brief Adds one occurrence of a digit.
         * @param c Character to count; non-digits are reported as errors.
         */
        constexpr void operator<<(const char &c) noexcept
        {
            if (etl::is_digit(c))
                hash_numbers[c - '0']++;
            else
                etl::io::println_error("the char is not a support digit or char");
        }

        /**
         * @brief Adds each digit in a string to its corresponding count.
         * @param s String whose characters will be counted.
         */
        inline void operator<<(const ocf::str &s) noexcept
        {
            for (const char &c : s)
                *this << c;
        }

        /**
         * @brief Gets the occurrence count for a digit.
         * @param c Digit character to query.
         * @return The stored count for the digit.
         * @warning The implementation indexes directly using c - '0';
         * callers should pass a decimal digit.
         */
        constexpr size_t operator[](const char &c) noexcept
        {
            return hash_numbers[c - '0'];
        }

        /**
         * @brief Checks whether the character's indexed count is nonzero.
         * @param c Character to query.
         * @return Whether the count at the implementation's character-derived
         * index is greater than zero.
         * @warning This method accepts printable characters but the backing
         * array contains only ten digit counts; use decimal digits only.
         */
        constexpr bool contains(const char &c) noexcept
        {
            return (c >= ' ' && c <= '~') ? hash_numbers[c - ' '] > 0 : false;
        }
    };

    /**
     * @brief Counts occurrences of ASCII characters from NUL through '~'.
     *
     * Values outside this range are ignored on insertion and return zero
     * when queried.
     */
    class enum_ascii
    {
    private:
        ocf::vec<size_t> count;

    protected:
        /** @brief Allocates and zero-initializes counters for the supported range. */
        inline void allocate_ascii() noexcept
        {
            for (char start = '\0'; start <= '~'; start++)
                count.push_back(0);
        }

    public:
        /** @brief Constructs an empty ASCII character counter. */
        enum_ascii() { allocate_ascii(); }

        /** @brief Destroys the ASCII character counter. */
        ~enum_ascii() = default;

        /**
         * @brief Constructs a counter initialized from a string.
         * @param s String whose characters are counted.
         */
        enum_ascii(const ocf::str& s) {
            allocate_ascii();
            for(char c : s) {
                count[c]++;
            }
        }

        /**
         * @brief Adds one occurrence of a supported ASCII character.
         * @param c Character to count; characters above '~' are ignored.
         */
        constexpr void operator<<(const char &c) noexcept
        {
            if (c >= '\0' && c <= '~')
                count[c]++;
        }

        /**
         * @brief Adds each supported character in a string.
         * @param s String whose characters are counted.
         */
        inline void operator<<(const ocf::str &s) noexcept
        {
            for (const char &c : s)
                *this << c;
        }

        /**
         * @brief Gets the count for a supported ASCII character.
         * @param c Character to query.
         * @return The stored count, or zero if c is outside the supported range.
         */
        constexpr size_t operator[](const char &c) noexcept
        {
            return (c >= '\0' && c <= '~') ? count[c] : 0;
        }

        /**
         * @brief Compares the occurrence counts of two ASCII counters.
         * @param other Counter to compare with.
         * @return true if every stored character count matches.
         */
        constexpr bool operator==(const enum_ascii &other) noexcept
        {
            for (size_t i = 0; i < count.size(); i++)
            {
                if (count[i] != other.count[i])
                    return false;
            }
            return true;
        }
        
        /**
         * @brief Adds a count to one character.
         * @param value Pair containing the character and the count to add.
         */
        constexpr void operator+=(const std::pair<char, size_t>& value) noexcept {
            count[value.first] += value.second;
        }

        /**
         * @brief Subtracts a count from one character.
         * @param value Pair containing the character and the count to subtract.
         */
        constexpr void operator-=(const std::pair<char, size_t>& value) noexcept {
            count[value.first] -= value.second;
        }

        /**
         * @brief Adds a count for every character in a string.
         * @param value Pair containing the string and count to add per character.
         */
        inline void operator+=(const std::pair<ocf::str, size_t>& value) {
            for(char c : value.first) count[c] += value.second;
        }

        /**
         * @brief Subtracts a count for every character in a string.
         * @param value Pair containing the string and count to subtract per character.
         */
        inline void operator-=(const std::pair<ocf::str, size_t>& value) {
            for(char c : value.first) count[c] -= value.second;
        }

        /**
         * @brief Compares this counter with another for inequality.
         * @param other Counter to compare with.
         * @return true if the counters differ.
         */
        constexpr bool operator!=(const enum_ascii &other) { return !(*this == other); }

        /**
         * @brief Checks whether a supported character has a nonzero count.
         * @param c Character to query.
         * @return true if the character is in range and has been counted.
         */
        constexpr bool contains(const char &c) noexcept
        {
            return (c >= '\0' && c <= '~') ? count[c] > 0 : false;
        }

        /** @brief Resets all supported character counts to zero. */
        inline void clear() noexcept {
            for(char c = '\0'; c <= '~'; c++) count[c] = 0;
        }
    };
}

#endif // ETL___ENUM_HPP