//
// Created by gbellizio on 19/04/23.
//

#include "Monolopy.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    using namespace std::string_view_literals;

    const auto names = std::vector{"A"sv, "B"sv};
    auto monopoly = Monopoly(names);

    return 0;
}