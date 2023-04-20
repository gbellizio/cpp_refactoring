//
// Created by gbellizio on 19/04/23.
//

#include "Player.h"
#include <algorithm>
#include <cassert>
#include <limits>

Player::Player(std::string name) noexcept
    : m_name{std::move(name)} {
}

const std::string &Player::name() const {
    return m_name;
}

int Player::budget() const noexcept {
    return m_budget;
}

void Player::buy_asset(int price) {
    assert(price >= 0 && m_budget >= price);

    m_budget -= price;
}

void Player::pay(int amount) {
    assert(amount >= 0 && m_budget >= amount);

    m_budget -= amount;
}

void Player::income_from_rent(int amount) {
    assert(amount >= 0 && std::numeric_limits<int>::max() - m_budget >= amount);

    m_budget += amount;
}
