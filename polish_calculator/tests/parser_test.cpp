//
// Created by gbellizio on 14/04/23.
//

#include "parser.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Parser", "[parser]") {

    SECTION("zero length input") {
        auto parser = Parser{""};
        REQUIRE_FALSE(parser.next());
    }

    SECTION("empty input") {
        auto parser = Parser{"            "};
        REQUIRE_FALSE(parser.next());
    }

    SECTION("valid input") {
        auto parser = Parser{"  *  -12345  +6789  "};
        auto tok = parser.next();
        REQUIRE(tok);
        REQUIRE(tok->type == TokenType::operation);
        REQUIRE(tok->fragment == "*");

        tok = parser.next();
        REQUIRE(tok);
        REQUIRE(tok->type == TokenType::operand);
        REQUIRE(tok->fragment == "-12345");

        tok = parser.next();
        REQUIRE(tok);
        REQUIRE(tok->type == TokenType::operand);
        REQUIRE(tok->fragment == "+6789");

        tok = parser.next();
        REQUIRE_FALSE(tok);
    }

    SECTION("invalid input") {
        auto parser = Parser{"1hello"};
        auto tok = parser.next();
        REQUIRE_FALSE(tok);
    }
}