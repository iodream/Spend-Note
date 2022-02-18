#include "BalanceRepository.h"

#include "DatabaseNames.h"

namespace db
{

BalanceRepository::BalanceRepository(pqxx::connection& db_connection) : m_db_connection(db_connection)
{
}

Money BalanceRepository::CalculateBalance(IdType user_id)
{
	try
	{
		pqxx::work w{m_db_connection};
		auto total_income_row = w.exec1(
			"SELECT COALESCE(SUM(" + db::income::AMOUNT + "), 0) " +
			"FROM " + db::income::TABLE_NAME +
			" WHERE " +
				db::income::USER_ID + " = " + w.quote(user_id) + " AND " +
				db::income::EXPIRATION_TIME + " > LOCALTIMESTAMP" + ";");

		auto total_outcome_row = w.exec1(
			"SELECT COALESCE(SUM(" + db::product::AMOUNT + " * " + db::product::PRICE + "), 0) " +
			"FROM " + db::product::TABLE_NAME + " JOIN " + db::list::TABLE_NAME +
			" ON " + db::product::TABLE_NAME + "." + db::product::LIST_ID + " = " + db::list::TABLE_NAME + "." + db::list::ID +
			" WHERE " + db::list::USER_ID + " = " + w.quote(user_id) + " AND " + db::product::IS_BOUGHT + ";");

		w.commit();

		return total_income_row.front().as<Money>() - total_outcome_row.front().as<Money>();
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
}

Money BalanceRepository::CalculatePlannedBalance(IdType user_id)
{
	try
	{
		pqxx::work w{m_db_connection};
		auto total_income_row = w.exec1(
			"SELECT COALESCE(SUM(" + db::income::AMOUNT + "), 0) " +
			"FROM " + db::income::TABLE_NAME +
			" WHERE " +
				db::income::USER_ID + " = " + w.quote(user_id) + " AND " +
				db::income::EXPIRATION_TIME + " > LOCALTIMESTAMP" + ";");

		auto total_outcome_row = w.exec1(
			"SELECT COALESCE(SUM(" + db::product::AMOUNT + " * " + db::product::PRICE + "), 0) " +
			"FROM " + db::product::TABLE_NAME + " JOIN " + db::list::TABLE_NAME +
			" ON " + db::product::TABLE_NAME + "." + db::product::LIST_ID + " = " + db::list::TABLE_NAME + "." + db::list::ID +
			" WHERE " + db::list::USER_ID + " = " + w.quote(user_id) + ";");

		w.commit();

		return total_income_row.front().as<Money>() - total_outcome_row.front().as<Money>();
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
}

}
