#include <unordered_map>
#include <string>

#pragma once
#ifndef METACORE___ADVA___TOKEN_HPP
#define METACORE___ADVA___TOKEN_HPP

namespace meta {

    namespace adva {

        size_t enum_counter = 0;

        class hash_enum {
            private:
            std::unordered_map<std::string, size_t> enumMap;
            public:
            hash_enum() = default;
            ~hash_enum() = default;

            constexpr inline void addToken(const std::string& enum_val) noexcept {
                enumMap[enum_val] = enum_counter;
                enum_counter++;
            }

            constexpr inline size_t size() noexcept {
                return enumMap.size();
            }

            inline auto begin() noexcept {
                return enumMap.begin();
            }

            inline auto end() noexcept {
                return enumMap.end();
            }

            constexpr inline void operator+=(const std::string& enum_val) noexcept { addToken(enum_val); }
        
            constexpr inline size_t operator[](const std::string& enum_val) noexcept { return enumMap.at(enum_val); }
        };

        template<typename T, typename U>
        class node {
            private:
            U centerElement;
            std::unordered_map<T, U> center;
            public:
            node() = default;
            ~node() = default;
            node(const U& element) noexcept : centerElement(element) {}

            void add(const T& key) noexcept { center[key] = centerElement; }

            void set(const U& element) noexcept { centerElement = element; }

            size_t size() noexcept { return center.size() }

            auto get() noexcept { return center; }

            U operator[](const T& key) { return center.at(key); }

            void operator+=(const T& key) noexcept { add(key); }
        };

        class token {};
    }
}

#endif // METACORE___ADVA___TOKEN_HPP