//
// Created by gbellizio on 14/04/23.
//

#include "solver_error.h"

SolverError::SolverError(std::string_view message)
    : m_message(message.data(), message.size()) {
}

SolverError::~SolverError() noexcept = default;

const char *SolverError::what() const noexcept {
    return m_message.c_str();
}
