#include "StatisticsRepository.h"

#include "Exceptions/NonexistentResource.h"
#include "DatabaseNames.h"

namespace db
{

StatisticsRepository::StatisticsRepository(pqxx::connection& db_connection) : m_db_connection(db_connection)
{
}

std::vector<ExpensePerCategory> StatisticsRepository::ExpensesPerCategory(IdType user_id)
{
	try
	{
		pqxx::work w{m_db_connection};

		if (DoesUserExist(user_id, w))
		{
			throw NonexistentResource("User with id = " + std::to_string(user_id) + " not found");
		}

		pqxx::result expenses = w.exec(
			"SELECT " +
				product::CATEGORY_ID +
				", COALESCE(SUM(" + product::AMOUNT+ " * " + product::PRICE + "), 0) AS " + statistics::TOTAL_PRICE +
			" FROM " + product::TABLE_NAME +
			" JOIN " + list::TABLE_NAME +
			" ON " + product::TABLE_NAME + "." + product::LIST_ID + " = " + list::TABLE_NAME + "." + list::ID +
			" WHERE " +
				list::TABLE_NAME + "." + list::USER_ID + " = " + w.quote(user_id) + " AND " +
				product::PURCHASE_DATE + " > LOCALTIMESTAMP - INTERVAL '1 WEEK' " +
			"GROUP BY " + product::CATEGORY_ID + ";");

		w.commit();

		std::vector<ExpensePerCategory> result(expenses.size());
		std::transform(expenses.begin(), expenses.end(), result.begin(), [](const pqxx::row& row){
			ExpensePerCategory expense;
			expense.category_id = row[product::CATEGORY_ID].as<IdType>();
			expense.amount = row[statistics::TOTAL_PRICE].as<Money>();
			return expense;
		});

		return result;
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
}

std::vector<ExpensePercentagePerCategory> StatisticsRepository::ExpensesPercentagePerCategory(IdType user_id)
{
	try
	{
		pqxx::work w{m_db_connection};

		if (DoesUserExist(user_id, w))
		{
			throw NonexistentResource("User with id = " + std::to_string(user_id) + " not found");
		}

		auto total_expenses = w.query_value<Money>(
			"SELECT COALESCE(SUM(" + db::product::AMOUNT + " * " + db::product::PRICE + "), 0) " +
			"FROM " + db::product::TABLE_NAME + " JOIN " + db::list::TABLE_NAME +
			" ON " +
				db::product::TABLE_NAME + "." + db::product::LIST_ID + " = " +
				db::list::TABLE_NAME + "." + db::list::ID +
			" WHERE " +
				db::list::USER_ID + " = " + w.quote(user_id) + " AND " +
				db::product::IS_BOUGHT + " AND " +
				product::PURCHASE_DATE + " > LOCALTIMESTAMP - INTERVAL '1 WEEK';");

		if (total_expenses == 0)
		{
			return {};
		}

		pqxx::result expenses = w.exec(
			"SELECT " +
				product::CATEGORY_ID +
				", COALESCE(SUM(" + product::AMOUNT+ " * " + product::PRICE + "), 0) / (" +
				w.quote(total_expenses) + "::DECIMAL) * 100 AS " + statistics::TOTAL_PRICE +
			" FROM " + product::TABLE_NAME +
			" JOIN " + list::TABLE_NAME +
			" ON " +
				product::TABLE_NAME + "." + product::LIST_ID + " = " +
				list::TABLE_NAME + "." + list::ID +
			" WHERE " +
				list::TABLE_NAME + "." + list::USER_ID + " = " + w.quote(user_id) + " AND " +
				product::PURCHASE_DATE + " > LOCALTIMESTAMP - INTERVAL '1 WEEK' " +
			"GROUP BY " + product::CATEGORY_ID + ";");

		w.commit();

		std::vector<ExpensePercentagePerCategory> result(expenses.size());
		std::transform(expenses.begin(), expenses.end(), result.begin(), [](const pqxx::row& row){
			ExpensePercentagePerCategory expense;
			expense.category_id = row[product::CATEGORY_ID].as<IdType>();
			expense.percentage = row[statistics::TOTAL_PRICE].as<double>();
			return expense;
		});

		return result;
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
}

std::vector<ExpensePerDay> StatisticsRepository::ExpensesDynamics(IdType user_id)
{
	try
	{
		pqxx::work w{m_db_connection};

		if (DoesUserExist(user_id, w))
		{
			throw NonexistentResource("User with id = " + std::to_string(user_id) + " not found");
		}

		pqxx::result expences = w.exec(
			"SELECT DATE(" + product::PURCHASE_DATE + ") AS " + statistics::PURCHASE_DATE + ", COALESCE(SUM(" + product::AMOUNT+ " * " + product::PRICE + "), 0) AS " + statistics::TOTAL_PRICE +
			" FROM " + product::TABLE_NAME +
			" JOIN " + list::TABLE_NAME + " ON " + product::TABLE_NAME + "." + product::LIST_ID + " = " + list::TABLE_NAME + "." + list::ID +
			" WHERE " +
				list::TABLE_NAME + "." + list::USER_ID + " = " + w.quote(user_id) + " AND " +
				product::PURCHASE_DATE + " > LOCALTIMESTAMP - INTERVAL '1 WEEK' " +
			"GROUP BY DATE(" + product::PURCHASE_DATE + ");");

		w.commit();

		std::vector<ExpensePerDay> result(expences.size());
		std::transform(expences.begin(), expences.end(), result.begin(), [](const pqxx::row& row) {
			ExpensePerDay expense;
			expense.day = row[statistics::PURCHASE_DATE].as<Date>();
			expense.amount = row[statistics::TOTAL_PRICE].as<Money>();
			return expense;
		});

		return result;
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
}

bool StatisticsRepository::DoesUserExist(IdType user_id, pqxx::work& work)
{
	pqxx::result user_ids = work.exec(
		"SELECT " + user::ID +
		" FROM " + user::TABLE_NAME +
		" WHERE " + user::ID + " = " + work.quote(user_id) + ";");
	return user_ids.empty();
}

}
