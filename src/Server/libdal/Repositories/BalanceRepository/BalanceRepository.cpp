#include "BalanceRepository.h"

namespace
{
	const std::string INCOME_TABLE_NAME = "Income";
	const std::string INCOME_AMOUNT_FIELD = "amount";
	const std::string INCOME_USER_ID_FIELD = "userId";

	const std::string PRODUCT_TABLE_NAME = "Product";
	const std::string PRODUCT_AMOUNT_FIELD = "amount";
	const std::string PRODUCT_PRICE_FIELD = "price";
	const std::string PRODUCT_IS_BOUGHT_FIELD = "isBought";
	const std::string PRODUCT_LIST_ID_FIELD = "listId";

	const std::string LIST_TABLE_NAME = "List";
	const std::string LIST_ID_FIELD = "id";
	const std::string LIST_USER_ID_FIELD = "userId";
}

BalanceRepository::BalanceRepository(pqxx::connection& db_connection) : m_db_connection(db_connection)
{
}

Money BalanceRepository::CalculateBalance(IdType user_id)
{
	try
	{
		pqxx::work w{m_db_connection};
		auto total_income_row = w.exec1(
			"SELECT SUM(" + INCOME_AMOUNT_FIELD + ")" +
			" FROM " + INCOME_TABLE_NAME +
			" WHERE " + INCOME_USER_ID_FIELD + " = " + w.quote(user_id) + ";");

		auto total_outcome_row = w.exec1(
			"SELECT SUM(" + PRODUCT_AMOUNT_FIELD + " * " + PRODUCT_PRICE_FIELD + ") " +
			"FROM " + PRODUCT_TABLE_NAME + " JOIN " + LIST_TABLE_NAME +
			" ON " + PRODUCT_TABLE_NAME + "." + PRODUCT_LIST_ID_FIELD + " = " + LIST_TABLE_NAME + "." + LIST_ID_FIELD +
			" WHERE " + LIST_USER_ID_FIELD + " = " + w.quote(user_id) + " AND " + PRODUCT_IS_BOUGHT_FIELD + ";");

		w.commit();

		return total_income_row.front().as<Money>() + total_outcome_row.front().as<Money>();
	}
	catch(const pqxx::pqxx_exception& e)
	{
		throw DatabaseFailure();
	}
}

Money BalanceRepository::CalculatePlannedBalance(IdType user_id)
{
	try
	{
		pqxx::work w{m_db_connection};
		auto total_income_row = w.exec1(
			"SELECT SUM(" + INCOME_AMOUNT_FIELD + ")" +
			" FROM " + INCOME_TABLE_NAME +
			" WHERE " + INCOME_USER_ID_FIELD + " = " + w.quote(user_id) + ";");

		auto total_outcome_row = w.exec1(
			"SELECT SUM(" + PRODUCT_AMOUNT_FIELD + " * " + PRODUCT_PRICE_FIELD + ") " +
			"FROM " + PRODUCT_TABLE_NAME + " JOIN " + LIST_TABLE_NAME +
			" ON " + PRODUCT_TABLE_NAME + "." + PRODUCT_LIST_ID_FIELD + " = " + LIST_TABLE_NAME + "." + LIST_ID_FIELD +
			" WHERE " + LIST_USER_ID_FIELD + " = " + w.quote(user_id) + ";");

		w.commit();

		return total_income_row.front().as<Money>() + total_outcome_row.front().as<Money>();
	}
	catch(const pqxx::pqxx_exception& e)
	{
		throw DatabaseFailure();
	}
}
