//
// Created by gbellizio on 14/04/23.
//

#pragma once


#include <memory>
#include <optional>
#include <string_view>

class Solver final {
public:
    Solver();
    ~Solver();

    double solve(std::string_view input);

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};
