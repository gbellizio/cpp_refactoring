#include "Monolopy.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>

using namespace ::std;
using namespace std::string_literals;

inline const auto players = std::vector{"Peter"s, "Ekaterina"s, "Alexander"s};

inline TEST_CASE("GetPlayersListReturnCorrectList", "[LAB2]") {
    auto monopoly = Monopoly{players};

    const auto expect_players = Monopoly::PlayerList{
            Player{"Peter"},
            Player{"Ekaterina"},
            Player{"Alexander"},
    };

    REQUIRE_THAT(monopoly.GetPlayerList(), Catch::Matchers::RangeEquals(expect_players, [](const auto &lhs, const auto &rhs) {
                     return std::tuple(lhs.name(), lhs.budget()) == std::tuple(rhs.name(), rhs.budget());
                 }));
    REQUIRE(true);
}

TEST_CASE("GetFieldsListReturnCorrectList", "[LAB2]") {
    auto monopoly = Monopoly{players};

    const auto expected_companies = Monopoly::CompanyList{
            Company::make_company<Company::CompanyType::AUTO>("Ford"),
            Company::make_company<Company::CompanyType::FOOD>("MCDonald"),
            Company::make_company<Company::CompanyType::CLOTHER>("Lamoda"),
            Company::make_company<Company::CompanyType::TRAVEL>("Air Balti"),
            Company::make_company<Company::CompanyType::TRAVEL>("Nordavia"),
            Company::make_company<Company::CompanyType::FOOD>("MCDonald"),
            Company::make_company<Company::CompanyType::AUTO>("TESLA"),
    };

    REQUIRE_THAT(monopoly.GetCompanyList(), Catch::Matchers::RangeEquals(expected_companies, [](const auto &lhs, const auto &rhs) {
                     const auto lhs_fd = lhs.financial_data();
                     const auto rhs_fd = rhs.financial_data();
                     return std::tuple(lhs.name(), lhs.type(), lhs_fd.price, lhs_fd.rent) ==
                            std::tuple(rhs.name(), rhs.type(), rhs_fd.price, rhs_fd.rent);
                 }));
}

TEST_CASE("PlayerBuyNoOwnedCompanies", "[LAB2]") {
    const auto company_name = "Ford";
    auto monopoly = Monopoly{players};

    auto company = monopoly.GetCompanyByName(company_name);
    REQUIRE(company);

    REQUIRE_NOTHROW(monopoly.BuyCompany(players[0], company->name()));

    auto player = monopoly.GetPlayerByName(players[0]);
    REQUIRE(player);
    REQUIRE(player->budget() == Player::StartingBudget - company->financial_data().price);

    auto holder = monopoly.GetHolder(company->name());

    REQUIRE(holder);
    REQUIRE(holder->name() == player->name());
}

TEST_CASE("PlayerCantBuyItsOwnedCompanies", "[LAB2]") {
    const auto company_name = "Ford";
    auto monopoly = Monopoly{players};

    auto company = monopoly.GetCompanyByName(company_name);
    REQUIRE(company);

    REQUIRE_NOTHROW(monopoly.BuyCompany(players[0], company->name()));

    auto player = monopoly.GetPlayerByName(players[0]);
    REQUIRE(player);
    REQUIRE(player->budget() == Player::StartingBudget - company->financial_data().price);

    auto holder = monopoly.GetHolder(company->name());

    REQUIRE(holder);
    REQUIRE(holder->name() == player->name());

    REQUIRE_THROWS(monopoly.BuyCompany(players[0], company->name()));
}

TEST_CASE("PlayerCantBuyOtherPlayerOwnedCompanies", "[LAB2]") {
    const auto company_name = "Ford";
    auto monopoly = Monopoly{players};

    auto company = monopoly.GetCompanyByName(company_name);
    REQUIRE(company);

    REQUIRE_NOTHROW(monopoly.BuyCompany(players[0], company->name()));

    auto player = monopoly.GetPlayerByName(players[0]);
    REQUIRE(player);
    REQUIRE(player->budget() == Player::StartingBudget - company->financial_data().price);

    auto holder = monopoly.GetHolder(company->name());

    REQUIRE(holder);
    REQUIRE(holder->name() == player->name());

    REQUIRE_THROWS(monopoly.BuyCompany(players[1], company->name()));
}

TEST_CASE("RentaShouldBeCorrectTransferMoney", "[LAB2]") {
    const auto company_name = "Ford";
    auto monopoly = Monopoly{players};

    auto company = monopoly.GetCompanyByName(company_name);
    REQUIRE(company);
    REQUIRE_NOTHROW(monopoly.BuyCompany(players[0], company->name()));
    REQUIRE_NOTHROW(monopoly.PayRentForCompany(players[1], company_name));

    const auto financial_data = company->financial_data();

    auto player1 = monopoly.GetPlayerByName(players[0]);
    auto player2 = monopoly.GetPlayerByName(players[1]);
    REQUIRE(player1);
    REQUIRE(player2);

    REQUIRE((player1->budget() == (Player::StartingBudget - financial_data.price + financial_data.rent)));
    REQUIRE((player2->budget() == (Player::StartingBudget - financial_data.rent)));
}

TEST_CASE("PayToBankShouldBeCorrectTransferMoney", "[LAB2]") {
    auto monopoly = Monopoly{players};
    REQUIRE_NOTHROW(monopoly.PayToBank(players[0]));

    auto player = monopoly.GetPlayerByName(players[0]);
    REQUIRE(player);
    REQUIRE((player->budget() == (Player::StartingBudget - Monopoly::BankTax)));
}

TEST_CASE("PayForPrisonShouldBeCorrectTransferMoney", "[LAB2]") {
    auto monopoly = Monopoly{players};
    REQUIRE_NOTHROW(monopoly.PayForPrison(players[0]));

    auto player = monopoly.GetPlayerByName(players[0]);
    REQUIRE(player);
    REQUIRE((player->budget() == (Player::StartingBudget - Monopoly::PrisonTax)));
}