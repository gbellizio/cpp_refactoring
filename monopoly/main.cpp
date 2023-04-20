//
// Created by gbellizio on 19/04/23.
//

#include "Monolopy.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    using namespace std::string_literals;

    const auto names = std::vector{"A"s, "B"s};
    auto monopoly = Monopoly(names);

    return 0;
}