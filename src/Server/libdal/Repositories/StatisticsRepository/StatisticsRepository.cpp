#include "StatisticsRepository.h"

#include "Exceptions/NonexistentResource.h"
#include "DatabaseNames.h"

namespace db
{

StatisticsRepository::StatisticsRepository(pqxx::connection& db_connection) : m_db_connection(db_connection)
{
}

std::vector<std::pair<IdType, Money>> StatisticsRepository::ExpensesPerCategoryWeekly(IdType user_id)
{
	try
	{
		pqxx::work w{m_db_connection};

		pqxx::result user_ids = w.exec(
			"SELECT " + user::ID +
			" FROM " + user::TABLE_NAME +
			" WHERE " + user::ID + " = " + w.quote(user_id) + ";");
		if (user_ids.empty())
		{
			auto message = "User with id = " + std::to_string(user_id) + " not found";
			throw NonexistentResource(message);
		}

		pqxx::result expences = w.exec(
			"SELECT " + product::CATEGORY_ID + ", COALESCE(SUM(" + product::AMOUNT+ " * " + product::PRICE + ", 0) AS " + statistics::TOTAL_PRICE +
			" FROM " + product::TABLE_NAME +
			" JOIN " + list::TABLE_NAME + " ON " + product::TABLE_NAME + "." + product::LIST_ID + " = " + list::TABLE_NAME + "." + list::ID +
			" WHERE " + list::TABLE_NAME + "." + user::ID + " = " + w.quote(user_id) + " AND " + product::PURCHASE_DATE + " < LOCALTIMESTAMP - INTERVAL '1 WEEK' " +
			"GROUP BY " + product::CATEGORY_ID + ";");

		w.commit();

		std::vector<std::pair<IdType, Money>> result(expences.size());
		std::transform(expences.begin(), expences.end(), result.begin(), [](const pqxx::row& row){
			return std::make_pair(
				row[product::CATEGORY_ID].as<IdType>(),
				row[statistics::TOTAL_PRICE].as<Money>());
		});

		return result;
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
}

std::vector<std::pair<Date, Money>> StatisticsRepository::ExpencesDynamicsWeekly(IdType user_id)
{
	try
	{
		pqxx::work w{m_db_connection};

		pqxx::result user_ids = w.exec(
			"SELECT " + user::ID +
			" FROM " + user::TABLE_NAME +
			" WHERE " + user::ID + " = " + w.quote(user_id) + ";");
		if (user_ids.empty())
		{
			auto message = "User with id = " + std::to_string(user_id) + " not found";
			throw NonexistentResource(message);
		}

		pqxx::result expences = w.exec(
			"SELECT DATE(" + product::PURCHASE_DATE + ") AS " + statistics::PURCHASE_DATE + ", COALESCE(SUM(" + product::AMOUNT+ " * " + product::PRICE + ", 0) AS " + statistics::TOTAL_PRICE +
			" FROM " + product::TABLE_NAME +
			" JOIN " + list::TABLE_NAME + " ON " + product::TABLE_NAME + "." + product::LIST_ID + " = " + list::TABLE_NAME + "." + list::ID +
			" WHERE " + list::TABLE_NAME + "." + user::ID + " = " + w.quote(user_id) + " AND " + product::PURCHASE_DATE + " < LOCALTIMESTAMP - INTERVAL '1 WEEK' " +
			"GROUP BY DATE(" + product::PURCHASE_DATE + ");");

		w.commit();

		std::vector<std::pair<Date, Money>> result(expences.size());
		std::transform(expences.begin(), expences.end(), result.begin(), [](const pqxx::row& row) {
			return std::make_pair(
				row[statistics::PURCHASE_DATE].as<Date>(),
				row[statistics::TOTAL_PRICE].as<Money>());
		});

		return result;
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
}

}
