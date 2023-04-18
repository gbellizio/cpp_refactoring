//
// Created by gbellizio on 14/04/23.
//

#pragma once

#include <exception>
#include <string>
#include <string_view>

class SolverError : public std::exception {
public:
    explicit SolverError(std::string_view message);

    ~SolverError() noexcept override;

    [[nodiscard]] const char *what() const noexcept override;

private:
    const std::string m_message;
};
