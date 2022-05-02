#include "PeriodicProductRepository.h"

#include <algorithm>
#include "Types.h"
#include "Exceptions/DatabaseFailure.h"
#include "Exceptions/SQLFailure.h"
#include "Exceptions/NonexistentResource.h"
#include "DatabaseNames.h"

namespace db
{

PeriodicProductRepository::PeriodicProductRepository(pqxx::connection& db_connection) : m_database_connection(db_connection)
{

}

std::optional<IdType> PeriodicProductRepository::Add(const PeriodicProduct& product)
{
	try
	{
		pqxx::work w(m_database_connection);
		pqxx::result id_rows = w.exec(
			"INSERT INTO " + periodicProduct::TABLE_NAME + " (" +
				periodicProduct::LIST_ID + ", " +
				periodicProduct::CATEGORY_ID + ", " +
				periodicProduct::NAME + ", " +
				periodicProduct::PRICE + ", " +
				periodicProduct::AMOUNT + ", " +
				periodicProduct::PRIORITY + ", " +
				periodicProduct::PERIOD_ID + ", " +
				periodicProduct::NEXT_ADD_DATE + ", " +
				periodicProduct::ADD_UNTIL +
			") VALUES (" +
				w.quote(product.list_id) + ", " +
				w.quote(product.category_id) + ", " +
				w.quote(product.name) + ", " +
				w.quote(product.price) + ", " +
				w.quote(product.amount) + ", " +
				w.quote(product.product_priority) + ", " +
				w.quote(product.period_id) + ", " +
				w.quote(product.next_add_date) + ", " +
				w.quote(product.add_until) + ") " +
			"RETURNING " + periodicProduct::ID + ";");
		w.commit();
		auto id_row = id_rows.front();
		return id_row[periodicProduct::ID].as<IdType>();
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

std::optional<PeriodicProduct> PeriodicProductRepository::GetById(IdType id)
{
	try
	{
		pqxx::nontransaction w(m_database_connection);
		pqxx::result product_rows = w.exec(
			"SELECT " +
				periodicProduct::ID + ", " +
				periodicProduct::LIST_ID + ", " +
				periodicProduct::CATEGORY_ID + ", " +
				periodicProduct::NAME + ", " +
				periodicProduct::PRICE + ", " +
				periodicProduct::AMOUNT + ", " +
				periodicProduct::PRIORITY + ", " +
				periodicProduct::PERIOD_ID + ", " +
				periodicProduct::NEXT_ADD_DATE + ", " +
				periodicProduct::ADD_UNTIL +
			" FROM " + periodicProduct::TABLE_NAME +
			" WHERE " + periodicProduct::ID + " = " + w.quote(id) + ";");

		if (!product_rows.empty())
		{
			return ProductFromRow(product_rows.front());
		}
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}

	return std::nullopt;
}

std::vector<PeriodicProduct> PeriodicProductRepository::GetByListId(IdType list_id)
{
	std::vector<PeriodicProduct> products;

	try
	{
		pqxx::work w(m_database_connection);

		pqxx::result list_ids = w.exec(
			"SELECT " + list::ID +
			" FROM " + list::TABLE_NAME +
			" WHERE " + list::ID + " = " + w.quote(list_id) + ";");

		if (list_ids.empty())
		{
			throw NonexistentResource("List with id = " + std::to_string(list_id) + " not found");
		}

		pqxx::result product_rows = w.exec(
			"SELECT " +
				periodicProduct::ID + ", " +
				periodicProduct::LIST_ID + ", " +
				periodicProduct::CATEGORY_ID + ", " +
				periodicProduct::NAME + ", " +
				periodicProduct::PRICE + ", " +
				periodicProduct::AMOUNT + ", " +
				periodicProduct::PRIORITY + ", " +
				periodicProduct::PERIOD_ID + ", " +
				periodicProduct::NEXT_ADD_DATE + ", " +
				periodicProduct::ADD_UNTIL +
			" FROM " + periodicProduct::TABLE_NAME +
			" WHERE " + periodicProduct::LIST_ID + " = " + w.quote(list_id) + ";");

		products.resize(product_rows.size());
		std::transform(product_rows.cbegin(), product_rows.cend(), products.begin(), ProductFromRow);
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}

	return products;
}

bool PeriodicProductRepository::Update(const PeriodicProduct& product)
{
	try
	{
		pqxx::work w(m_database_connection);
		auto result = w.exec(
			"SELECT " + periodicProduct::ID +
			" FROM  " + periodicProduct::TABLE_NAME +
			" WHERE " + periodicProduct::ID + " = " + w.quote(product.id));

		if (result.empty())
		{
			return false;
		}

		w.exec0(
				"UPDATE " + periodicProduct::TABLE_NAME +
				" SET " +
					periodicProduct::LIST_ID + " = " + w.quote(product.list_id) + ", " +
					periodicProduct::CATEGORY_ID + " = " + w.quote(product.category_id) + ", " +
					periodicProduct::NAME + " = " + w.quote(product.name) + ", " +
					periodicProduct::PRICE + " = " + w.quote(product.price) + ", " +
					periodicProduct::AMOUNT + " = " + w.quote(product.amount) + ", " +
					periodicProduct::PRIORITY + " = " + w.quote(product.product_priority) + ", " +
					periodicProduct::PERIOD_ID + " = " + w.quote(product.period_id) + ", " +
					periodicProduct::NEXT_ADD_DATE + " = " + w.quote(product.next_add_date) + ", " +
					periodicProduct::ADD_UNTIL +  + " = " + w.quote(product.add_until) +
				" WHERE " + periodicProduct::ID + " = " + w.quote(product.id) + ";");
		w.commit();
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
	return true;
}

bool PeriodicProductRepository::Remove(IdType id)
{
	try
	{
		pqxx::work w(m_database_connection);
		auto result = w.exec(
			"SELECT " + periodicProduct::ID +
			" FROM  " + periodicProduct::TABLE_NAME +
			" WHERE " + periodicProduct::ID + " = " + w.quote(id));

		if (result.empty())
		{
			return false;
		}
		w.exec0(
			"DELETE FROM " + periodicProduct::TABLE_NAME + " WHERE " + periodicProduct::ID + " = " + w.quote(id) + ";");
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

bool PeriodicProductRepository::CanUserEditProduct(IdType user_id, IdType product_id)
{
	try
	{
		pqxx::nontransaction w{m_database_connection};

		auto result = w.exec(
			"SELECT " + periodicProduct::TABLE_NAME + "." + periodicProduct::ID +
			" FROM " + periodicProduct::TABLE_NAME + " JOIN " + list::TABLE_NAME +
			" ON " + periodicProduct::LIST_ID + " = " + list::TABLE_NAME + "." + list::ID +
			" WHERE " +
				periodicProduct::TABLE_NAME + "." + periodicProduct::ID +" = "  + w.quote(product_id) + " AND " +
				list::USER_ID +" = "  + w.quote(user_id));

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

std::vector<PeriodType> PeriodicProductRepository::GetAllPeriodTypes()
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

bool PeriodicProductRepository::CanGenerate(IdType periodic_id)
{
	try
	{
		pqxx::nontransaction w{m_database_connection};

		auto result = w.exec(
			"SELECT " + periodicProduct::ID +
			" FROM " + periodicProduct::TABLE_NAME +
			" WHERE " +
				periodicProduct::ID +" = "  + w.quote(periodic_id) + " AND " +
				periodicProduct::NEXT_ADD_DATE + " <= current_date AND " +
				periodicProduct::NEXT_ADD_DATE + " < " + periodicProduct::ADD_UNTIL + ";");

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

bool PeriodicProductRepository::UpdateAddNext(const PeriodicProduct& product)
{
	try
	{
		pqxx::work w(m_database_connection);
		auto result = w.exec(
			"SELECT " + periodicProduct::ID +
			" FROM  " + periodicProduct::TABLE_NAME +
			" WHERE " + periodicProduct::ID + " = " + w.quote(product.id));

		if (result.empty())
		{
			return false;
		}

		w.exec0(
			"UPDATE " + periodicProduct::TABLE_NAME +
			" SET " + periodicProduct::NEXT_ADD_DATE + " = " + w.quote(product.next_add_date) + " + " + PeriodIdToString(product.period_id) + +
			" WHERE " + periodicProduct::ID + " = " + w.quote(product.id) + ";");
		w.commit();
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
	return true;
}

std::vector<PeriodicProduct> PeriodicProductRepository::GetByUserId(IdType user_id)
{
	std::vector<PeriodicProduct> products;

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

		pqxx::result product_rows = w.exec(
			"SELECT " +
				periodicProduct::TABLE_NAME + "." + periodicProduct::ID + ", " +
				periodicProduct::TABLE_NAME + "." + periodicProduct::LIST_ID + ", " +
				periodicProduct::TABLE_NAME + "." + periodicProduct::CATEGORY_ID + ", " +
				periodicProduct::TABLE_NAME + "." + periodicProduct::NAME + ", " +
				periodicProduct::TABLE_NAME + "." + periodicProduct::PRICE + ", " +
				periodicProduct::TABLE_NAME + "." + periodicProduct::AMOUNT + ", " +
				periodicProduct::TABLE_NAME + "." + periodicProduct::PRIORITY + ", " +
				periodicProduct::TABLE_NAME + "." + periodicProduct::PERIOD_ID + ", " +
				periodicProduct::TABLE_NAME + "." + periodicProduct::NEXT_ADD_DATE + ", " +
				periodicProduct::TABLE_NAME + "." + periodicProduct::ADD_UNTIL +
			" FROM " + periodicProduct::TABLE_NAME + " JOIN " + list::TABLE_NAME +
			" ON " + periodicProduct::LIST_ID + " = " + list::TABLE_NAME + "." + list::ID +
			" WHERE " + list::USER_ID + " = " + w.quote(user_id) + ";");

		products.resize(product_rows.size());
		std::transform(product_rows.cbegin(), product_rows.cend(), products.begin(), ProductFromRow);
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}

	return products;
}

PeriodicProduct PeriodicProductRepository::ProductFromRow(const pqxx::row& row)
{
	PeriodicProduct product;

	product.id = row[periodicProduct::ID].as<IdType>();
	product.list_id = row[periodicProduct::LIST_ID].as<IdType>();
	product.category_id = row[periodicProduct::CATEGORY_ID].as<IdType>();
	product.name = row[periodicProduct::NAME].as<std::string>();
	product.price = row[periodicProduct::PRICE].as<Money>();
	product.amount = row[periodicProduct::AMOUNT].as<int>();
	product.product_priority = row[periodicProduct::PRIORITY].as<int>();
	product.period_id = row[periodicProduct::PERIOD_ID].as<IdType>();
	product.next_add_date = row[periodicProduct::NEXT_ADD_DATE].as<Timestamp>();
	product.add_until = row[periodicProduct::ADD_UNTIL].get<Timestamp>();

	return product;
}

PeriodType PeriodicProductRepository::PeriodFromRow(const pqxx::row& row)
{
	PeriodType type;
	type.id = row[periodType::ID].as<IdType>();
	type.name = row[periodType::NAME].as<std::string>();

	return type;
}

std::string PeriodicProductRepository::PeriodIdToString(IdType id)
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
