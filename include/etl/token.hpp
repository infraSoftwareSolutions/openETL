#include <iostream>
#include "cformat/types.h"
#include "hash.hpp"
 
#pragma once
#ifndef ETL___TOKEN_HPP
#define ETL___TOKEN_HPP

namespace etl {        
    using token = std::pair<ocf::str, uint8_t>;

    class key_map {
        private:
        ocf::str keyWord;
        ocf::hash_map<ocf::str, ocf::str> elements;
        
        public:
        key_map() = default;
        
        ~key_map() = default;
        
        key_map(const ocf::str& element) noexcept : 
        keyWord(element) {}

        key_map(const key_map& other) noexcept : 
        keyWord(other.keyWord), 
        elements(other.elements) {}

        void set(const ocf::str& element) noexcept { keyWord = element; }

        const ocf::str& get() noexcept { return keyWord; }

        size_t size() noexcept { return elements.size(); }

        ocf::str operator[](const ocf::str& key) { return elements.at(key); }

        void operator<<(const ocf::str& element) noexcept { elements[element] = keyWord; }

        void operator=(const key_map& other) {
            keyWord = other.keyWord;
            elements = other.elements;
        }
    };

    class tokenizer {
        private:
        hash_enum id_number;
        ocf::vec<token> result;

        public:
        tokenizer() noexcept = default;
        ~tokenizer() noexcept = default;

        tokenizer(const hash_enum& idNum) noexcept : id_number(idNum) {}

        inline const ocf::vec<token>& get() noexcept { return result; }

        inline void operator<<(const ocf::str& token_name) noexcept {
            result.push_back(token(token_name, id_number[token_name]));
        }

        inline void operator<<(const ocf::vec<ocf::str>& tokens) noexcept {
            for(ocf::str token_name : tokens) {
                result.push_back(token(token_name, id_number[token_name]));
            }
        }

        inline token operator[](const size_t index) noexcept { return result[index]; }
    };
}

#endif // ETL___TOKEN_HPP