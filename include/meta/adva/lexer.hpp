#include "token.hpp"
#include "function.hpp"
#include "cfrost/structure.h"

#pragma once
#ifndef METACORE___ADVA___LEXER_HPP
#define METACORE___ADVA___LEXER_HPP

namespace meta {
    namespace adva {
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
}

#endif // METACORE___ADVA___LEXER_HPP