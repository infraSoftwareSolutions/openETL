#include <unordered_map>
#include <string>
#include <ctype.h>
#include <iostream>
#include <initializer_list>

#pragma once
#ifndef METACORE___ADVA___TOKEN_HPP
#define METACORE___ADVA___TOKEN_HPP

namespace meta {

    namespace adva {
        
        using token = std::pair<std::string, uint8_t>;

        class hash_enum {
            private:
            uint8_t counter = 0;
            std::unordered_map<std::string, uint8_t> objectMap;

            public:
            hash_enum() = default;
            ~hash_enum() = default;

            hash_enum(const std::initializer_list<std::string> &list) noexcept {
                for(std::string element : list) {
                    objectMap[element] = counter;
                    counter++;
                }
            }

            hash_enum(const hash_enum& other) noexcept : objectMap(other.objectMap) {}

            constexpr inline void add(const std::string& enum_val) noexcept {
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

            constexpr inline void operator<<(const std::string& enum_val) noexcept { add(enum_val); }
        
            constexpr inline uint8_t operator[](const std::string& enum_val) noexcept { return objectMap.at(enum_val); }

            inline void operator=(const hash_enum& other) noexcept {
                counter = other.counter;
                objectMap = other.objectMap;
            }
        };

        class key_map {
            private:
            std::string keyWord;
            std::unordered_map<std::string, std::string> elements;
            
            public:
            key_map() = default;
            
            ~key_map() = default;
            
            key_map(const std::string& element) noexcept : 
            keyWord(element) {}

            key_map(const key_map& other) noexcept : 
            keyWord(other.keyWord), 
            elements(other.elements) {}

            void set(const std::string& element) noexcept { keyWord = element; }

            const std::string& get() noexcept { return keyWord; }

            size_t size() noexcept { return elements.size(); }

            std::string operator[](const std::string& key) { return elements.at(key); }

            void operator<<(const std::string& element) noexcept { elements[element] = keyWord; }

            void operator=(const key_map& other) {
                keyWord = other.keyWord;
                elements = other.elements;
            }
        };

        class tokenizer {
            private:
            hash_enum id_number;
            std::vector<token> result;

            public:
            tokenizer() noexcept = default;
            ~tokenizer() noexcept = default;

            tokenizer(const hash_enum& idNum) noexcept : id_number(idNum) {}

            inline const std::vector<token>& get() noexcept { return result; }

            inline void operator<<(const std::string& token_name) noexcept {
                result.push_back(token(token_name, id_number[token_name]));
            }

            inline void operator<<(const std::vector<std::string>& tokens) noexcept {
                for(std::string token_name : tokens) {
                    result.push_back(token(token_name, id_number[token_name]));
                }
            }

            inline token operator[](const size_t index) noexcept { return result[index]; }
        };
    }
}

#endif // METACORE___ADVA___TOKEN_HPP