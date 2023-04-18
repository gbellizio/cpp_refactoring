//
// Created by gbellizio on 14/04/23.
//

#include "solver.h"
#include "parser.h"
#include "solver_error.h"
#include <charconv>
#include <fmt/format.h>
#include <optional>
#include <stack>
#include <variant>

namespace {
    double add(double op1, double op2) { return op1 + op2; }

    double subtract(double op1, double op2) { return op1 - op2; }

    double multiply(double op1, double op2) { return op1 * op2; }

    double divide(double op1, double op2) { return op1 / op2; }

    using operation_t = double (*)(double, double);
    using operand_t = double;
    using stack_item_t = std::variant<operation_t, operand_t>;

    inline stack_item_t make_operation(const Token &token) {
        switch (token.fragment[0]) {
            case '+':
                return add;
            case '-':
                return subtract;
            case '*':
                return multiply;
            case '/':
                return divide;
            default:
                throw SolverError{fmt::format(R"(invalid operator "{}")", token.fragment)};
        }
    }

    inline stack_item_t make_operand(const Token &token) {
        if (double result{}; std::from_chars(token.fragment.data(),
                                             token.fragment.data() + token.fragment.size(),
                                             result)
                                     .ec == std::errc{}) {
            return result;
        }
        throw SolverError{fmt::format(R"(invalid operand "{})", token.fragment)};
    }

}// namespace

class Solver::Impl {
public:
    void handle_token(const Token &token) {
        if (token.type == TokenType::operation) {
            handle_operation(token);
        } else if (token.type == TokenType::operand) {
            handle_operand(token);
        }
    }

    double result() {
        if (tokens.size() == 1 && std::holds_alternative<operand_t>(tokens.top())) {
            auto result = std::get<operand_t>(tokens.top());
            tokens.pop();
            return result;
        }

        throw SolverError("invalid input");
    }

private:
    std::stack<stack_item_t> tokens;

    void handle_operation(const Token &token) {
        if (tokens.empty() || std::holds_alternative<operation_t>(tokens.top())) {
            tokens.push(make_operation(token));
        } else {
            throw SolverError{"invalid input"};
        }
    }

    void handle_operand(const Token &token) {
        if (tokens.empty()) {
            throw SolverError{"invalid input"};
        } else if (std::holds_alternative<operation_t>(tokens.top())) {
            tokens.push(make_operand(token));
        } else {
            auto val1 = std::get<operand_t>(tokens.top());
            tokens.pop();
            auto op = std::get<operation_t>(tokens.top());
            tokens.pop();
            auto val2 = std::get<operand_t>(make_operand(token));
            tokens.emplace(op(val1, val2));
        }
    }
};

Solver::Solver() {
    m_impl = std::make_unique<Impl>();
}

Solver::~Solver() = default;

double Solver::solve(std::string_view input) {
    auto parser = Parser{input};

    while (auto tok = parser.next()) {
        m_impl->handle_token(*tok);
    }

    return m_impl->result();
}
