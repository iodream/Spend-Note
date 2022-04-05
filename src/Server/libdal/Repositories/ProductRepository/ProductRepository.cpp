#include "ProductRepository.h"

#include <algorithm>
#include "Types.h"
#include "Exceptions/DatabaseFailure.h"
#include "Exceptions/SQLFailure.h"
#include "Exceptions/NonexistentResource.h"
#include "DatabaseNames.h"

namespace db
{

ProductRepository::ProductRepository(pqxx::connection& db_connection) : m_database_connection(db_connection)
{

}

std::optional<IdType> ProductRepository::Add(const Product& product)
{
	try
	{
		pqxx::work w(m_database_connection);
		pqxx::result id_rows = w.exec(
			"INSERT INTO " + db::product::TABLE_NAME + " (" +
				db::product::LIST_ID + ", " +
				db::product::CATEGORY_ID + ", " +
				db::product::NAME + ", " +
				db::product::PRICE + ", " +
				db::product::AMOUNT + ", " +
				db::product::PRIORITY + ", " +
				db::product::IS_BOUGHT + ", " +
				db::product::ADD_DATE + ", " +
				db::product::PURCHASE_DATE + ", " +
				db::product::BUY_UNTIL_DATE +
			") VALUES (" +
				w.quote(product.list_id) + ", " +
				w.quote(product.category_id) + ", " +
				w.quote(product.name) + ", " +
				w.quote(product.price) + ", " +
				w.quote(product.amount) + ", " +
				w.quote(product.product_priority) + ", " +
				w.quote(product.is_bought) + ", " +
				w.quote(product.add_date) + ", " +
				w.quote(product.purchase_date) + ", " +
				w.quote(product.buy_until_date) + ") " +
			"RETURNING " + db::product::ID + ";");
		w.commit();
		auto id_row = id_rows.front();
		return id_row[db::product::ID].as<IdType>();
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

std::optional<Product> ProductRepository::GetById(IdType id)
{
	try
	{
		pqxx::nontransaction w(m_database_connection);
		pqxx::result product_rows = w.exec(
				"SELECT " +
					db::product::ID + ", " +
					db::product::LIST_ID + ", " +
					db::product::CATEGORY_ID + ", " +
					db::product::NAME + ", " +
					db::product::PRICE + ", " +
					db::product::AMOUNT + ", " +
					db::product::PRIORITY + ", " +
					db::product::IS_BOUGHT + ", " +
					db::product::ADD_DATE + ", " +
					db::product::PURCHASE_DATE + ", " +
					db::product::BUY_UNTIL_DATE +
				" FROM " + db::product::TABLE_NAME +
				" WHERE " + db::product::ID + " = " + w.quote(id) + ";");

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

std::vector<Product> ProductRepository::GetByListId(IdType list_id)
{
	std::vector<Product> products;

	try
	{
		pqxx::work w(m_database_connection);

		pqxx::result list_ids = w.exec(
			"SELECT " + db::list::ID +
			" FROM " + db::list::TABLE_NAME +
			" WHERE " +
				db::list::ID + " = " + w.quote(list_id) + ";");
		if (list_ids.empty())
		{
			throw NonexistentResource("List with id = " + std::to_string(list_id) + " not found");
		}

		pqxx::result product_rows = w.exec(
			"SELECT " +
				db::product::ID + ", " +
				db::product::LIST_ID + ", " +
				db::product::CATEGORY_ID + ", " +
				db::product::NAME + ", " +
				db::product::PRICE + ", " +
				db::product::AMOUNT + ", " +
				db::product::PRIORITY + ", " +
				db::product::IS_BOUGHT + ", " +
				db::product::ADD_DATE + ", " +
				db::product::PURCHASE_DATE + ", " +
				db::product::BUY_UNTIL_DATE +
			" FROM " + db::product::TABLE_NAME +
			" WHERE " + db::product::LIST_ID + " = " + w.quote(list_id) + ";");

		products.resize(product_rows.size());
		std::transform(product_rows.cbegin(), product_rows.cend(), products.begin(), ProductFromRow);
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}

	return products;
}

std::vector<Product> ProductRepository::GetDailyList(IdType user_id)
{
	std::vector<Product> products;

	try
	{
		pqxx::work w(m_database_connection);

		pqxx::result user_ids = w.exec(
			"SELECT " + db::user::ID +
			" FROM " + db::user::TABLE_NAME +
			" WHERE " +
				db::user::ID + " = " + w.quote(user_id) + ";");
		if (user_ids.empty())
		{
			throw NonexistentResource("User with id = " + std::to_string(user_id) + " not found");
		}

		pqxx::result product_rows = w.exec(
			"SELECT " +
				db::product::TABLE_NAME + "." + db::product::ID + ", " +
				db::product::TABLE_NAME + "." + db::product::LIST_ID + ", " +
				db::product::TABLE_NAME + "." + db::product::CATEGORY_ID + ", " +
				db::product::TABLE_NAME + "." + db::product::NAME + ", " +
				db::product::TABLE_NAME + "." + db::product::PRICE + ", " +
				db::product::TABLE_NAME + "." + db::product::AMOUNT + ", " +
				db::product::TABLE_NAME + "." + db::product::PRIORITY + ", " +
				db::product::TABLE_NAME + "." + db::product::IS_BOUGHT + ", " +
				db::product::TABLE_NAME + "." + db::product::ADD_DATE + ", " +
				db::product::TABLE_NAME + "." + db::product::PURCHASE_DATE + ", " +
				db::product::TABLE_NAME + "." + db::product::BUY_UNTIL_DATE +
			" FROM " + db::product::TABLE_NAME +
			" JOIN " + db::list::TABLE_NAME +
			" ON " + db::product::TABLE_NAME + "." + db::product::LIST_ID + " = " + db::list::TABLE_NAME + "." + db::list::ID +
			" WHERE DATE(" + db::product::BUY_UNTIL_DATE + ") = current_date AND " + db::list::USER_ID + " = " + w.quote(user_id) + " AND NOT " + db::product::IS_BOUGHT + ";");

		products.resize(product_rows.size());
		std::transform(product_rows.cbegin(), product_rows.cend(), products.begin(), ProductFromRow);
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}

	return products;
}

bool ProductRepository::Update(const Product& product)
{
	try
	{
		pqxx::work w(m_database_connection);
		auto result = w.exec("SELECT " + db::product::ID + " FROM  " + db::product::TABLE_NAME + " WHERE " + db::product::ID + " = " + w.quote(product.id));
		if (result.empty())
		{
			return false;
		}

		w.exec0(
				"UPDATE " + db::product::TABLE_NAME +
				" SET " +
					db::product::LIST_ID + " = " + w.quote(product.list_id) + ", " +
					db::product::CATEGORY_ID + " = " + w.quote(product.category_id) + ", " +
					db::product::NAME + " = " + w.quote(product.name) + ", " +
					db::product::PRICE + " = " + w.quote(product.price) + ", " +
					db::product::AMOUNT + " = " + w.quote(product.amount) + ", " +
					db::product::PRIORITY + " = " + w.quote(product.product_priority) + ", " +
					db::product::IS_BOUGHT + " = " + w.quote(product.is_bought) + ", " +
					db::product::ADD_DATE + " = " + w.quote(product.add_date) + ", " +
					db::product::PURCHASE_DATE + " = " + w.quote(product.purchase_date) + ", " +
					db::product::BUY_UNTIL_DATE +  + " = " + w.quote(product.buy_until_date) +
				" WHERE " + db::product::ID + " = " + w.quote(product.id) + ";");
		w.commit();
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
	return true;
}

bool ProductRepository::Remove(IdType id)
{
	try
	{
		pqxx::work w(m_database_connection);
		auto result = w.exec("SELECT " + db::product::ID + " FROM  " + db::product::TABLE_NAME + " WHERE " + db::product::ID + " = " + w.quote(id));
		if (result.empty())
		{
			return false;
		}
		w.exec0("DELETE FROM " + db::product::TABLE_NAME + " WHERE " + db::product::ID + " = " + w.quote(id) + ";");
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

bool ProductRepository::CanUserEditProduct(IdType user_id, IdType product_id)
{
	try
	{
		pqxx::nontransaction w{m_database_connection};

		auto result = w.exec(
			"SELECT " + db::product::TABLE_NAME + "." + db::product::ID +
			" FROM " + db::product::TABLE_NAME + " JOIN " + db::list::TABLE_NAME +
			" ON " + db::product::LIST_ID + " = " + db::list::TABLE_NAME + "." + db::list::ID +
			" WHERE " +
				db::product::TABLE_NAME + "." + db::product::ID +" = "  + w.quote(product_id) + " AND " +
				db::list::USER_ID +" = "  + w.quote(user_id));

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

Product ProductRepository::ProductFromRow(const pqxx::row& row)
{
	Product product;

	product.id = row[db::product::ID].as<IdType>();
	product.list_id = row[db::product::LIST_ID].as<IdType>();
	product.category_id = row[db::product::CATEGORY_ID].as<IdType>();
	product.name = row[db::product::NAME].as<std::string>();
	product.price = row[db::product::PRICE].as<Money>();
	product.amount = row[db::product::AMOUNT].as<int>();
	product.product_priority = row[db::product::PRIORITY].as<int>();
	product.is_bought = row[db::product::IS_BOUGHT].as<bool>();
	product.add_date = row[db::product::ADD_DATE].as<Timestamp>();
	product.purchase_date = row[db::product::PURCHASE_DATE].get<Timestamp>();
	product.buy_until_date = row[db::product::BUY_UNTIL_DATE].get<Timestamp>();

	return product;
}

}
