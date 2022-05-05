#include "PeriodicIncomeRepository.h"

#include <algorithm>
#include "Types.h"
#include "Exceptions/DatabaseFailure.h"
#include "Exceptions/SQLFailure.h"
#include "Exceptions/NonexistentResource.h"
#include "DatabaseNames.h"

namespace db
{

PeriodicIncomeRepository::PeriodicIncomeRepository(pqxx::connection& db_connection)
	: m_database_connection(db_connection)
{

}

std::optional<IdType> PeriodicIncomeRepository::Add(const PeriodicIncome& income)
{
	try
	{
		pqxx::work w(m_database_connection);
		pqxx::result id_rows = w.exec(
			"INSERT INTO " + periodicIncome::TABLE_NAME + " (" +
				periodicIncome::NAME + ", " +
				periodicIncome::USER_ID + ", " +
				periodicIncome::AMOUNT + ", " +
				periodicIncome::CATEGORY_ID + ", " +
				periodicIncome::PERIOD_ID + ", " +
				periodicIncome::NEXT_ADD_DATE + ", " +
				periodicIncome::ADD_UNTIL +
			") VALUES (" +
				w.quote(income.name) + ", " +
				w.quote(income.user_id) + ", " +
				w.quote(income.amount) + ", " +
				w.quote(income.category_id) + ", " +
				w.quote(income.period_id) + ", " +
				w.quote(income.next_add_date) + ", " +
				w.quote(income.add_until) + ") " +
			"RETURNING " + periodicIncome::ID + ";");
		w.commit();
		auto id_row = id_rows.front();
		return id_row[periodicIncome::ID].as<IdType>();
	}
	catch(const pqxx::sql_error& e)
	{
		throw SQLFailure(e.what());
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
	return std::nullopt;
}

std::optional<PeriodicIncome> PeriodicIncomeRepository::GetById(IdType id)
{
	try
	{
		pqxx::nontransaction w(m_database_connection);
		pqxx::result income_rows = w.exec(
			"SELECT " +
				periodicIncome::ID + ", " +
				periodicIncome::NAME + ", " +
				periodicIncome::USER_ID + ", " +
				periodicIncome::AMOUNT + ", " +
				periodicIncome::CATEGORY_ID + ", " +
				periodicIncome::PERIOD_ID + ", " +
				periodicIncome::NEXT_ADD_DATE + ", " +
				periodicIncome::ADD_UNTIL +
			" FROM " + periodicIncome::TABLE_NAME +
			" WHERE " + periodicIncome::ID + " = " + w.quote(id) + ";");

		if (!income_rows.empty())
		{
			return IncomeFromRow(income_rows.front());
		}
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}

	return std::nullopt;
}

std::vector<PeriodicIncome> PeriodicIncomeRepository::GetAllIncomes(IdType user_id)
{
	std::vector<PeriodicIncome> incomes;

	try
	{
		pqxx::work w(m_database_connection);

		pqxx::result user_ids = w.exec(
			"SELECT " + user::ID +
			" FROM " + user::TABLE_NAME +
			" WHERE " + user::ID + " = " + w.quote(user_id) + ";");

		if (user_ids.empty())
		{
			throw NonexistentResource("User with id = " + std::to_string(user_id) + " not found");
		}

		pqxx::result income_rows = w.exec(
			"SELECT " +
				periodicIncome::ID + ", " +
				periodicIncome::NAME + ", " +
				periodicIncome::USER_ID + ", " +
				periodicIncome::AMOUNT + ", " +
				periodicIncome::CATEGORY_ID + ", " +
				periodicIncome::PERIOD_ID + ", " +
				periodicIncome::NEXT_ADD_DATE + ", " +
				periodicIncome::ADD_UNTIL +
			" FROM " + periodicIncome::TABLE_NAME +
			" WHERE " + periodicIncome::USER_ID+ " = " + w.quote(user_id) + ";");

		incomes.resize(income_rows.size());
		std::transform(income_rows.cbegin(), income_rows.cend(), incomes.begin(), IncomeFromRow);
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}

	return incomes;
}

bool PeriodicIncomeRepository::Update(const PeriodicIncome& income)
{
	try
	{
		pqxx::work w(m_database_connection);
		auto result = w.exec(
			"SELECT " + periodicIncome::ID +
			" FROM  " + periodicIncome::TABLE_NAME +
			" WHERE " + periodicIncome::ID + " = " + w.quote(income.id));

		if (result.empty())
		{
			return false;
		}

		w.exec0(
			"UPDATE " + periodicIncome::TABLE_NAME +
			" SET " +
				periodicIncome::NAME + " = " + w.quote(income.name) + ", " +
				periodicIncome::USER_ID + " = " + w.quote(income.user_id) + ", " +
				periodicIncome::AMOUNT + " = " + w.quote(income.amount) + ", " +
				periodicIncome::CATEGORY_ID + " = " + w.quote(income.category_id) + ", " +
				periodicIncome::PERIOD_ID + " = " + w.quote(income.period_id) + ", " +
				periodicIncome::NEXT_ADD_DATE + " = " + w.quote(income.next_add_date) + ", " +
				periodicIncome::ADD_UNTIL +  + " = " + w.quote(income.add_until) +
			" WHERE " + periodicIncome::ID + " = " + w.quote(income.id) + ";");
		w.commit();
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
	return true;
}

bool PeriodicIncomeRepository::Remove(IdType id)
{
	try
	{
		pqxx::work w(m_database_connection);
		auto result = w.exec(
			"SELECT " + periodicIncome::ID +
			" FROM  " + periodicIncome::TABLE_NAME +
			" WHERE " + periodicIncome::ID + " = " + w.quote(id));

		if (result.empty())
		{
			return false;
		}
		w.exec0(
			"DELETE FROM " + periodicIncome::TABLE_NAME +
			" WHERE " + periodicIncome::ID + " = " + w.quote(id) + ";");
		w.commit();
	}
	catch(const pqxx::sql_error& e)
	{
		throw SQLFailure(e.what());
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
	return true;
}

bool PeriodicIncomeRepository::CanUserEditIncome(IdType user_id, IdType income_id)
{
	try
	{
		pqxx::nontransaction w{m_database_connection};

		auto result = w.exec(
			"SELECT " + periodicIncome::ID +
			" FROM " + periodicIncome::TABLE_NAME +
			" WHERE " +
				periodicIncome::ID +" = "  + w.quote(income_id) + " AND " +
				periodicIncome::USER_ID +" = "  + w.quote(user_id));

		if (result.empty())
		{
			return false;
		}
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}

	return true;
}

std::vector<PeriodType> PeriodicIncomeRepository::GetAllPeriodTypes()
{
	std::vector<PeriodType> period_types;

	try
	{
		pqxx::work w(m_database_connection);

		pqxx::result period_rows = w.exec(
			"SELECT " +
				periodType::ID + ", " +
				periodType::NAME +
			" FROM " + periodType::TABLE_NAME + ";");

		period_types.resize(period_rows.size());
		std::transform(period_rows.cbegin(), period_rows.cend(), period_types.begin(), PeriodFromRow);
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}

	return period_types;
}

bool PeriodicIncomeRepository::CanGenerate(IdType periodic_id)
{
	try
	{
		pqxx::nontransaction w{m_database_connection};

		auto result = w.exec(
			"SELECT " + periodicIncome::ID +
			" FROM " + periodicIncome::TABLE_NAME +
			" WHERE " +
				periodicIncome::ID +" = "  + w.quote(periodic_id) + " AND " +
				periodicIncome::NEXT_ADD_DATE + " <= current_date AND " +
				periodicIncome::NEXT_ADD_DATE + " < " + periodicIncome::ADD_UNTIL + ";");

		if (result.empty())
		{
			return false;
		}
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}

	return true;
}

bool PeriodicIncomeRepository::UpdateAddNext(const PeriodicIncome& income)
{
	try
	{
		pqxx::work w(m_database_connection);
		auto result = w.exec(
			"SELECT " + periodicIncome::ID +
			" FROM  " + periodicIncome::TABLE_NAME +
			" WHERE " + periodicIncome::ID + " = " + w.quote(income.id));

		if (result.empty())
		{
			return false;
		}

		w.exec0(
			"UPDATE " + periodicIncome::TABLE_NAME +
			" SET " + periodicIncome::NEXT_ADD_DATE + " = " + w.quote(income.next_add_date) + " + " + PeriodIdToString(income.period_id) + +
			" WHERE " + periodicIncome::ID + " = " + w.quote(income.id) + ";");
		w.commit();
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
	return true;
}


PeriodicIncome PeriodicIncomeRepository::IncomeFromRow(const pqxx::row &row)
{
	PeriodicIncome income;

	income.id = row[periodicIncome::ID].as<IdType>();
	income.name = row[periodicIncome::NAME].as<std::string>();
	income.user_id = row[periodicIncome::USER_ID].as<IdType>();
	income.amount = row[periodicIncome::AMOUNT].as<int>();
	income.category_id = row[periodicIncome::CATEGORY_ID].as<IdType>();
	income.period_id = row[periodicIncome::PERIOD_ID].as<IdType>();
	income.next_add_date = row[periodicIncome::NEXT_ADD_DATE].as<Timestamp>();
	income.add_until = row[periodicIncome::ADD_UNTIL].get<Timestamp>();

	return income;
}

PeriodType PeriodicIncomeRepository::PeriodFromRow(const pqxx::row& row)
{
	PeriodType type;
	type.id = row[periodType::ID].as<IdType>();
	type.name = row[periodType::NAME].as<std::string>();

	return type;
}

std::string PeriodicIncomeRepository::PeriodIdToString(IdType id)
{
	switch (id)
	{
		case 1:
			return "'1 DAY'";
		case 2:
			return "'1 WEEK'";
		case 3:
			return "'1 MONTH'";
		case 4:
			return "'1 YEAR'";
	}
}
}
