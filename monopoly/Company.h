//
// Created by gbellizio on 19/04/23.
//

#pragma once


#include <string>
#include <string_view>
#include <unordered_map>

class Company {
public:
    enum class CompanyType {
        AUTO,
        FOOD,
        TRAVEL,
        CLOTHER
    };

    struct FinancialData {
        int price;
        int rent;
    };

    template<CompanyType type>
    static Company make_company(std::string name);

    const std::string &name() const;
    CompanyType type() const;
    const FinancialData &financial_data() const;

private:
    std::string m_name;
    CompanyType m_type;
    FinancialData m_financial_data;

    Company(std::string name, CompanyType type);
};

template<Company::CompanyType type>
inline Company Company::make_company(std::string name) {
    return {std::move(name), type};
}
