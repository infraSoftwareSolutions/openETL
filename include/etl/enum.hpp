#include "cfrost/types.h"
#include "function.hpp"
#include "io.hpp"

#pragma once
#ifndef ETL___ENUM_HPP
#define ETL___ENUM_HPP

namespace etl
{
    class enum_decimal
    {
    private:
        ocf::vec<size_t> hash_numbers;

    protected:
        void allocate_numbers()
        {
            for (char c = '0'; c <= '9'; c++)
                hash_numbers.push_back(0);
        }

    public:
        enum_decimal() { allocate_numbers(); }
        ~enum_decimal() = default;

        constexpr void operator<<(const char &c) noexcept
        {
            if (etl::is_digit(c))
                hash_numbers[c - '0']++;
            else
                etl::io::println_error("the char is not a support digit or char");
        }

        inline void operator<<(const ocf::str &s) noexcept
        {
            for (const char &c : s)
                *this << c;
        }

        constexpr size_t operator[](const char &c) noexcept
        {
            return hash_numbers[c - '0'];
        }

        constexpr bool contains(const char &c) noexcept
        {
            return (c >= ' ' && c <= '~') ? hash_numbers[c - ' '] > 0 : false;
        }
    };

    class enum_ascii
    {
    private:
        std::vector<size_t> count;

    protected:
        inline void allocate_ascii() noexcept
        {
            for (char start = '\0'; start <= '~'; start++)
                count.push_back(0);
        }

    public:
        enum_ascii() { allocate_ascii(); }
        ~enum_ascii() = default;

        enum_ascii(const std::string& s) {
            allocate_ascii();
            for(char c : s) {
                count[c]++;
            }
        }

        constexpr void operator<<(const char &c) noexcept
        {
            if (c >= '\0' && c <= '~')
                count[c]++;
        }

        inline void operator<<(const std::string &s) noexcept
        {
            for (const char &c : s)
                *this << c;
        }

        constexpr size_t operator[](const char &c) noexcept
        {
            return (c >= '\0' && c <= '~') ? count[c] : 0;
        }

        constexpr bool operator==(const enum_ascii &other) noexcept
        {
            for (size_t i = 0; i < count.size(); i++)
            {
                if (count[i] != other.count[i])
                    return false;
            }
            return true;
        }
        
        constexpr void operator+=(const std::pair<char, size_t>& value) noexcept {
            count[value.first] += value.second;
        }

        constexpr void operator-=(const std::pair<char, size_t>& value) noexcept {
            count[value.first] -= value.second;
        }

        inline void operator+=(const std::pair<std::string, size_t>& value) {
            for(char c : value.first) count[c] += value.second;
        }

        inline void operator-=(const std::pair<std::string, size_t>& value) {
            for(char c : value.first) count[c] -= value.second;
        }

        constexpr bool operator!=(const enum_ascii &other) { return !(*this == other); }

        constexpr bool contains(const char &c) noexcept
        {
            return (c >= '\0' && c <= '~') ? count[c] > 0 : false;
        }

        inline void clear() noexcept {
            for(char c = '\0'; c <= '~'; c++) count[c] = 0;
        }
    };
}

#endif // ETL___ENUM_HPP