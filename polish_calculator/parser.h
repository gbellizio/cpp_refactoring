//
// Created by gbellizio on 14/04/23.
//

#pragma once

#include <optional>
#include <string>
#include <string_view>
#include <vector>

enum class TokenType {
    operand,
    operation
};

struct Token {
    TokenType type;
    std::string_view fragment;
};

class Parser final {
public:
    Parser() = delete;

    explicit Parser(std::string_view input);

    std::optional<Token> next();

private:
    const std::string m_input;
    std::string::size_type m_curr{};
};
