#include "IncomeRepository.h"

namespace
{
    const std::string& TABLE_NAME = "Income";
    const std::string& ID_FIELD = "id";
    const std::string& INCOME_NAME = "name";
    const std::string& USER_ID = "userId";
    const std::string& AMOUNT = "amount";
    const std::string& CATEGORY_ID = "categoryId";
    const std::string& ADD_TIME = "addTime";
    const std::string& EXPERATION_TIME = "expirationTime";
    const std::string& TABLE_WITH_CATEGORY = "IncomeCategory";
}

IncomeRepository::IncomeRepository(pqxx::connection& databaseConnection) : m_databaseConnection(databaseConnection)
{
}

void IncomeRepository::Add(const Income& income)
{
    pqxx::work w{m_databaseConnection};

    w.exec0("INSERT INTO " + TABLE_NAME + " (" + USER_ID + ", " + INCOME_NAME + ", " + AMOUNT + ", "
            + CATEGORY_ID + ", " + ADD_TIME + ", " + EXPERATION_TIME + ") " +
            "VALUES (" + w.quote(income.userId) + ", " + w.quote(income.name)+ ", " + w.quote(income.amount) + ", "
            + w.quote(income.categoryId) + ", " + w.quote(income.addTime) + ", "
            + w.quote(income.expoirationTime) + ");"
             );

     w.commit();
}

std::optional<Income> IncomeRepository::GetIncome(const idType& id)
{
    pqxx::work w{m_databaseConnection};

    try
    {
        pqxx::row income = w.exec1("SELECT * FROM " + TABLE_NAME + " WHERE " + ID_FIELD + " = "  + w.quote(id) + ";");

        if(!income[EXPERATION_TIME].is_null())
        {
            return Income{income[ID_FIELD].as<idType>(), income[USER_ID].as<idType>(),
                          income[INCOME_NAME].as<std::string>(), income[AMOUNT].as<double>(),
                          income[CATEGORY_ID].as<idType>(), income[ADD_TIME].as<std::string>(),
                          income[EXPERATION_TIME].as<std::string>()};
        }

        else if(income.empty())
               return std::nullopt;

        else
        {
            return Income{income[ID_FIELD].as<idType>(), income[USER_ID].as<idType>(),
                          income[INCOME_NAME].as<std::string>(), income[AMOUNT].as<double>(),
                          income[CATEGORY_ID].as<idType>(), income[ADD_TIME].as<std::string>()};
        }
    }
    catch(const pqxx::pqxx_exception& e)
    {
        throw DatabaseFailure();
    }
}

void IncomeRepository::Update(const Income& income)
{
    pqxx::work w{m_databaseConnection};

    try
    {
        w.exec0("UPDATE " + TABLE_NAME + " SET " + INCOME_NAME + " = " + w.quote(income.name) + ", "
                 + AMOUNT + " = " + w.quote(income.amount) + ", " + CATEGORY_ID + " = " + w.quote(income.categoryId) + ", "
                 + ADD_TIME + " = " + w.quote(income.addTime) + ", " + EXPERATION_TIME + " = " + w.quote(income.expoirationTime)
                 + " WHERE " + ID_FIELD + " = " + w.quote(income.id) + ";");
        w.commit();

    }
    catch(const pqxx::pqxx_exception& e)
    {
        throw DatabaseFailure();
    }
}

void IncomeRepository::Remuve(const idType& id)
{
    pqxx::work w{m_databaseConnection};

    try
    {
        w.exec0("DELETE FROM " + TABLE_NAME + " WHERE " + ID_FIELD + " = " + w.quote(id) + ";");
        w.commit();
    }
    catch(const pqxx::pqxx_exception& e)
    {
        throw DatabaseFailure();
    }
}
