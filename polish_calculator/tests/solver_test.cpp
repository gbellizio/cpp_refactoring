//
// Created by gbellizio on 14/04/23.
//

#include "solver.h"
#include "solver_error.h"
#include <catch2/catch_test_macros.hpp>
#include <limits>

TEST_CASE("Solver", "[solver]") {

    SECTION("zero length input") {
        auto solver = Solver{};
        REQUIRE_THROWS_AS(solver.solve(""), SolverError);
    }

    SECTION("empty input") {
        auto solver = Solver{};
        REQUIRE_THROWS_AS(solver.solve("        "), SolverError);
    }

    SECTION("binary operation") {
        auto input = "+ 25 25";
        auto solver = Solver{};
        auto result = solver.solve(input);
        REQUIRE(result == 50);
    }

    SECTION("complex operation") {
        auto input = "* + 25 25 2";
        auto solver = Solver{};
        auto result = solver.solve(input);
        REQUIRE(result == 100);
    }

    SECTION("signed operands 1") {
        auto input = "* -5 2";
        auto solver = Solver{};
        auto result = solver.solve(input);
        REQUIRE(result == -10);
    }

    SECTION("signed operands 2") {
        auto input = "* -5 -2";
        auto solver = Solver{};
        auto result = solver.solve(input);
        REQUIRE(result == 10);
    }

    SECTION("invalid input") {

        SECTION("missing operator") {
            auto input = "25 25";
            auto solver = Solver{};
            REQUIRE_THROWS_AS(solver.solve(input), SolverError);
        }

        SECTION("missing operand") {
            auto input = "* + 25 25";
            auto solver = Solver{};
            REQUIRE_THROWS_AS(solver.solve(input), SolverError);
        }
    }

    SECTION("division by zero") {
        auto input = "/ 1 0";
        auto solver = Solver{};
        auto result = solver.solve(input);
        REQUIRE(result == std::numeric_limits<double>::infinity());
    }
}