//
// Created by gbellizio on 19/04/23.
//

#pragma once

#include <list>
#include <string>
#include <string_view>

class Player {
public:
    static constexpr auto StartingBudget = 6000;

    explicit Player(std::string name) noexcept;

    [[nodiscard]] const std::string &name() const;

    [[nodiscard]] int budget() const noexcept;

    void buy_asset(int price);

    void pay(int amount);

    void income_from_rent(int amount);

private:
    std::string m_name;
    int m_budget{StartingBudget};
};
