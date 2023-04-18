#include "fmt/color.h"
#include "solver.h"
#include <exception>
#include <iostream>
#include <ostream>
#include <string>

int main() {
    fmt::print(fmt::emphasis::bold | fg(fmt::color::cyan), "Simple Polish notation calculator\n");

    Solver solver;

    while (std::cin.good()) {
        std::cout << "> ";
        std::string input;
        std::getline(std::cin, input);
        try {
            fmt::print(fmt::emphasis::bold | fg(fmt::color::green), "result: {}\n", solver.solve(input));
        } catch (const std::exception &ex) {
            fmt::print(fmt::emphasis::bold | fg(fmt::color::red), "error: {}\n", ex.what());
        }
    }

    return 0;
}
