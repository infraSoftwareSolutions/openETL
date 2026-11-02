#include "token.hpp"
#include "function.hpp"
#include "cfrost/types.h"

#pragma once
#ifndef ETL___LEXER_HPP
#define ETL___LEXER_HPP

namespace etl {
    class lexer {
        private:
        tokenizer line_tok;
        ocf::vec<ocf::str> split_line;

        public:
        lexer() noexcept = default;
        ~lexer() noexcept = default;

        lexer(tokenizer tok) noexcept : line_tok(tok) {}
    };
}

#endif // ETL___LEXER_HPP