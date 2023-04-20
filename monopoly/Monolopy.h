#pragma once

#include "Company.h"
#include "Player.h"
#include <memory>
#include <optional>
#include <vector>

class Monopoly {
public:
    static inline auto BankTax = 700;
    static inline auto PrisonTax = 1000;

    using PlayerList = std::list<Player>;
    using CompanyList = std::list<Company>;

    explicit Monopoly(const std::vector<std::string> &names);

    ~Monopoly();

    [[nodiscard]] PlayerList GetPlayerList() const;
    [[nodiscard]] CompanyList GetCompanyList() const;
    [[nodiscard]] std::optional<Player> GetPlayerByName(std::string_view name) const;

    void BuyCompany(std::string_view player_name, std::string_view company_name);

    std::optional<Company> GetCompanyByName(std::string_view name);
    void PayRentForCompany(std::string_view player_name, std::string_view company_name);
    void PayForPrison(std::string_view player_name);
    void PayToBank(std::string_view player_name);

    std::optional<Player> GetHolder(std::string_view company_name);

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};
