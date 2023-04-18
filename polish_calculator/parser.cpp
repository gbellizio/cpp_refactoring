//
// Created by gbellizio on 14/04/23.
//

#include "parser.h"
#include <algorithm>
#include <cctype>
#include <string_view>

namespace {

    enum class CharType {
        space,
        digit,
        sign,// -, +
        operation,
        invalid
    };

    enum class ParserTokenType {
        operand,
        operation,
        unknown
    };

    constexpr auto to_token_type(ParserTokenType t) {
        if (t == ParserTokenType::operand) {
            return TokenType::operand;
        } else {
            return TokenType::operation;
        }
    }

}// namespace

Parser::Parser(std::string_view input)
    : m_input{input.data(), input.size()} {
}

std::optional<Token> Parser::next() {
    auto begin = m_curr;
    auto last_char = CharType::invalid;
    auto token_type = ParserTokenType::unknown;

    while (m_curr < m_input.size()) {
        switch (const auto c = m_input[m_curr]) {
            case ' ':
                if (last_char == CharType::space || last_char == CharType::invalid) {
                    ++begin;
                }
                last_char = CharType::space;
                break;
            case '+':
            case '-':
                if (std::isdigit(m_input[m_curr + 1])) {
                    last_char = CharType::sign;
                } else {
                    token_type = ParserTokenType::operation;
                    last_char = CharType::operation;
                }
                break;
            case '*':
            case '/':
                token_type = ParserTokenType::operation;
                last_char = CharType::operation;
                break;
            default:
                if (std::isdigit(c)) {
                    token_type = ParserTokenType::operand;
                    last_char = CharType::digit;
                } else {
                    token_type = ParserTokenType::unknown;
                    last_char = CharType::invalid;
                }
                break;
        }

        if (last_char == CharType::invalid || (last_char == CharType::space && token_type != ParserTokenType::unknown)) {
            break;
        } else {
            ++m_curr;
        }
    }

    if (token_type != ParserTokenType::unknown) {
        return Token{to_token_type(token_type),
                     std::string_view{m_input.data() + begin, m_curr - begin}};
    }

    return std::nullopt;
}
