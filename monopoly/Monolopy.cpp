#include "Monolopy.h"
#include "Company.h"
#include "MonopolyException.h"
#include <fmt/format.h>
#include <optional>
#include <ranges>
#include <string_view>
#include <unordered_map>
#include <vector>

struct Monopoly::Impl {
    using Assets = std::list<std::string_view>;
    using PlayerAssets = std::unordered_map<std::string_view, Assets>;

    static inline const CompanyList companies = {
            Company::make_company<Company::CompanyType::AUTO>("Ford"),
            Company::make_company<Company::CompanyType::FOOD>("MCDonald"),
            Company::make_company<Company::CompanyType::CLOTHER>("Lamoda"),
            Company::make_company<Company::CompanyType::TRAVEL>("Air Balti"),
            Company::make_company<Company::CompanyType::TRAVEL>("Nordavia"),
            Company::make_company<Company::CompanyType::FOOD>("MCDonald"),
            Company::make_company<Company::CompanyType::AUTO>("TESLA"),
    };

    PlayerList players;
    PlayerAssets player_assets;


    explicit Impl(const std::vector<std::string> &names) {
        add_players(names);
    }

    void add_players(const std::vector<std::string> &names) {
        for (const auto &name: names) {
            players.emplace_back(name);
        }
    }

    [[nodiscard]] auto find_player_by_name(std::string_view name) {
        return std::ranges::find(players, name, &Player::name);
    }

    [[nodiscard]] auto find_company_by_name(std::string_view name) {
        return std::ranges::find(companies, name, &Company::name);
    }

    std::string_view asset_holder(std::string_view company_name) {
        for (const auto &[player, assets]: player_assets) {
            if (std::ranges::find(assets, company_name) != std::end(assets)) {
                return player;
            }
        }
        return {};
    }

    auto get_player_if_exists(std::string_view player_name) {
        if (auto it = find_player_by_name(player_name); it != std::end(players)) {
            return it;
        }
        throw MonopolyException(fmt::format(R"(Player "{}" not found!)", player_name));
    }

    auto get_company_if_exists(std::string_view company_name) {
        if (auto it = find_company_by_name(company_name); it != std::end(companies)) {
            return it;
        }
        throw MonopolyException(fmt::format(R"(Company "{}" not found!)", company_name));
    }

    void ensure_player_can_buy(const Player &p, const Company &c) {
        if (p.budget() < c.financial_data().price) {
            throw MonopolyException(fmt::format(R"(Player "{}" budget is not enough to buy company "{}": {} < {})",
                                                p.name(), c.name(), p.budget(), c.financial_data().price));
        }

        if (auto holder = asset_holder(c.name()); !holder.empty()) {
            throw MonopolyException(fmt::format(R"(Player "{}" budget can't buy company "{}": company is already hold by player "{}")",
                                                p.name(), c.name(), holder));
        }
    }

    void buy_company(std::string_view player_name, std::string_view company_name) {
        auto player_it = get_player_if_exists(player_name);
        auto company_it = get_company_if_exists(company_name);

        ensure_player_can_buy(*player_it, *company_it);

        player_it->buy_asset(company_it->financial_data().price);
        player_assets[player_name].emplace_back(company_name);
    }

    void ensure_player_has_to_pay_for(const Player &p, const Company &c) {
        auto holder = asset_holder(c.name());
        if (holder.empty()) {
            throw MonopolyException(fmt::format(R"(Player "{}" budget can't pay for free company "{}")",
                                                p.name(), c.name()));
        }

        if (holder == p.name()) {
            throw MonopolyException(fmt::format(R"(Player "{}" budget can't pay for its own company "{}")",
                                                p.name(), c.name()));
        }
    }

    void pay_rent_for_company(std::string_view player_name, std::string_view company_name) {
        auto player_it = get_player_if_exists(player_name);
        auto company_it = get_company_if_exists(company_name);

        ensure_player_has_to_pay_for(*player_it, *company_it);

        player_it->pay(company_it->financial_data().rent);
        find_player_by_name(asset_holder(company_name))->income_from_rent(company_it->financial_data().rent);
    }

    void pay_for_prison(std::string_view player_name) {
        auto it = get_player_if_exists(player_name);
        if (it->budget() < Monopoly::PrisonTax)
            throw MonopolyException(fmt::format(R"(Player "{}" budget is not enough to pay for prison tax: {} < {})",
                                                player_name, it->budget(), Monopoly::PrisonTax));

        it->pay(Monopoly::PrisonTax);
    }

    void pay_to_bank(std::string_view player_name) {
        auto it = get_player_if_exists(player_name);
        if (it->budget() < Monopoly::BankTax)
            throw MonopolyException(fmt::format(R"(Player "{}" budget is not enough to pay for bank tax: {} < {})",
                                                player_name, it->budget(), Monopoly::BankTax));

        it->pay(Monopoly::BankTax);
    }
};

Monopoly::Monopoly(const std::vector<std::string> &names)
    : m_impl{std::make_unique<Impl>(names)} {
}

Monopoly::~Monopoly() = default;

Monopoly::PlayerList Monopoly::GetPlayerList() const {
    return m_impl->players;
}

Monopoly::CompanyList Monopoly::GetCompanyList() const {
    return Monopoly::Impl::companies;
}

std::optional<Player> Monopoly::GetPlayerByName(std::string_view name) const {
    auto it = m_impl->find_player_by_name(name);

    return it == std::end(m_impl->players)
                   ? std::nullopt
                   : std::optional{*it};
}

void Monopoly::BuyCompany(std::string_view player_name, std::string_view company_name) {
    m_impl->buy_company(player_name, company_name);
}


std::optional<Company> Monopoly::GetCompanyByName(std::string_view name) {
    auto it = m_impl->find_company_by_name(name);

    return it == std::end(Monopoly::Impl::companies)
                   ? std::nullopt
                   : std::optional{*it};
}

void Monopoly::PayRentForCompany(std::string_view player_name, std::string_view company_name) {
    m_impl->pay_rent_for_company(player_name, company_name);
}

void Monopoly::PayForPrison(std::string_view player_name) {
    m_impl->pay_for_prison(player_name);
}

void Monopoly::PayToBank(std::string_view player_name) {
    m_impl->pay_to_bank(player_name);
}

std::optional<Player> Monopoly::GetHolder(std::string_view company_name) {
    return GetPlayerByName(m_impl->asset_holder(company_name));
}
