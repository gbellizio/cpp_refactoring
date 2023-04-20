//
// Created by gbellizio on 20/04/23.
//

#pragma once

#include <stdexcept>

class MonopolyException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;

    ~MonopolyException() noexcept override = default;
};
