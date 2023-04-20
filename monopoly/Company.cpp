//
// Created by gbellizio on 19/04/23.
//

#include "Company.h"

namespace {

    inline const auto CompanyTypeFinancialData = std::unordered_map<Company::CompanyType, Company::FinancialData>{
            {Company::CompanyType::AUTO, {500, 250}},
            {Company::CompanyType::FOOD, {250, 250}},
            {Company::CompanyType::TRAVEL, {700, 250}},
            {Company::CompanyType::CLOTHER, {100, 250}},
    };
}

Company::Company(std::string name, Company::CompanyType type)
    : m_name{std::move(name)},
      m_type{type},
      m_financial_data{CompanyTypeFinancialData.at(type)} {
}

const std::string &Company::name() const {
    return m_name;
}

Company::CompanyType Company::type() const {
    return m_type;
}

const Company::FinancialData &Company::financial_data() const {
    return m_financial_data;
}
