#include "ProductRepository.h"

#include <algorithm>
#include "Types.h"
#include "Exceptions/DatabaseFailure.h"
#include "Exceptions/SQLFailure.h"

namespace
{
	const std::string TABLE_NAME = "Product";
	const std::string ID_FIELD = "id";
	const std::string LIST_ID_FIELD = "listId";
	const std::string CATEGORY_ID_FIELD = "categoryId";
	const std::string NAME_FIELD = "name";
	const std::string PRICE_FIELD = "price";
	const std::string AMOUNT_FIELD = "amount";
	const std::string PRODUCT_PRIORITY_FIELD = "productPriority";
	const std::string IS_BOUGHT_FIELD = "isBought";
	const std::string ADD_DATE_FIELD = "addDate";
	const std::string PURCHASE_DATE_FIELD = "purchaseDate";
	const std::string BUY_UNTIL_DATE_FIELD = "buyUntilDate";
}

ProductRepository::ProductRepository(pqxx::connection& db_connection) : m_database_connection(db_connection)
{

}

std::optional<IdType> ProductRepository::Add(const Product& product)
{
	try
	{
		pqxx::work w(m_database_connection);
		pqxx::result id_rows = w.exec(
			"INSERT INTO " + TABLE_NAME + " (" +
				LIST_ID_FIELD + ", " +
				CATEGORY_ID_FIELD + ", " +
				NAME_FIELD + ", " +
				PRICE_FIELD + ", " +
				AMOUNT_FIELD + ", " +
				PRODUCT_PRIORITY_FIELD + ", " +
				IS_BOUGHT_FIELD + ", " +
				ADD_DATE_FIELD + ", " +
				PURCHASE_DATE_FIELD + ", " +
				BUY_UNTIL_DATE_FIELD +
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
				"RETURNING " + ID_FIELD + ";");
		w.commit();
		auto id_row = id_rows.front();
		return id_row[ID_FIELD].as<IdType>();
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
					ID_FIELD + ", " +
					LIST_ID_FIELD + ", " +
					CATEGORY_ID_FIELD + ", " +
					NAME_FIELD + ", " +
					PRICE_FIELD + ", " +
					AMOUNT_FIELD + ", " +
					PRODUCT_PRIORITY_FIELD + ", " +
					IS_BOUGHT_FIELD + ", " +
					ADD_DATE_FIELD + ", " +
					PURCHASE_DATE_FIELD + ", " +
					BUY_UNTIL_DATE_FIELD +
				" FROM " + TABLE_NAME +
				" WHERE " + ID_FIELD + " = " + w.quote(id) + ";");

		if (!product_rows.empty())
		{
			return ProductFromRow(product_rows.front());
		}
	}
	catch(const pqxx::pqxx_exception& e)
	{
		throw DatabaseFailure();
	}

	return std::nullopt;
}

std::vector<Product> ProductRepository::GetByListId(IdType list_id)
{
	std::vector<Product> products;

	try
	{
		pqxx::nontransaction w(m_database_connection);
		pqxx::result product_rows = w.exec(
				"SELECT " +
					ID_FIELD + ", " +
					LIST_ID_FIELD + ", " +
					CATEGORY_ID_FIELD + ", " +
					NAME_FIELD + ", " +
					PRICE_FIELD + ", " +
					AMOUNT_FIELD + ", " +
					PRODUCT_PRIORITY_FIELD + ", " +
					IS_BOUGHT_FIELD + ", " +
					ADD_DATE_FIELD + ", " +
					PURCHASE_DATE_FIELD + ", " +
					BUY_UNTIL_DATE_FIELD +
				" FROM " + TABLE_NAME +
				" WHERE " + LIST_ID_FIELD + " = " + w.quote(list_id) + ";");

		products.resize(product_rows.size());
		std::transform(product_rows.cbegin(), product_rows.cend(), products.begin(), ProductFromRow);
	}
	catch(const pqxx::pqxx_exception& e)
	{
		throw DatabaseFailure();
	}

	return products;
}

bool ProductRepository::Update(const Product& product)
{
	try
	{
		pqxx::work w(m_database_connection);
		auto result = w.exec("SELECT " + ID_FIELD + " FROM  " + TABLE_NAME + " WHERE " + ID_FIELD + " = " + w.quote(product.id));
		if (result.empty())
		{
			return false;
		}

		w.exec0(
				"UPDATE " + TABLE_NAME +
				" SET " +
					LIST_ID_FIELD + " = " + w.quote(product.list_id) + ", " +
					CATEGORY_ID_FIELD + " = " + w.quote(product.category_id) + ", " +
					NAME_FIELD + " = " + w.quote(product.name) + ", " +
					PRICE_FIELD + " = " + w.quote(product.price) + ", " +
					AMOUNT_FIELD + " = " + w.quote(product.amount) + ", " +
					PRODUCT_PRIORITY_FIELD + " = " + w.quote(product.product_priority) + ", " +
					IS_BOUGHT_FIELD + " = " + w.quote(product.is_bought) + ", " +
					ADD_DATE_FIELD + " = " + w.quote(product.add_date) + ", " +
					PURCHASE_DATE_FIELD + " = " + w.quote(product.purchase_date) + ", " +
					BUY_UNTIL_DATE_FIELD +  + " = " + w.quote(product.buy_until_date) + ", " +
				" WHERE " + ID_FIELD + " = " + w.quote(product.id) + ";");
		w.commit();
	}
	catch(const pqxx::pqxx_exception& e)
	{
		throw DatabaseFailure();
	}
	return true;
}

bool ProductRepository::Remove(IdType id)
{
	try
	{
		pqxx::work w(m_database_connection);
		auto result = w.exec("SELECT " + ID_FIELD + " FROM  " + TABLE_NAME + " WHERE " + ID_FIELD + " = " + w.quote(id));
		if (result.empty())
		{
			return false;
		}
		w.exec0("DELETE FROM " + TABLE_NAME + " WHERE " + ID_FIELD + " = " + w.quote(id) + ";");
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

Product ProductRepository::ProductFromRow(const pqxx::row& row)
{
	Product product;
	product.id = row[ID_FIELD].as<IdType>();
	product.list_id = row[LIST_ID_FIELD].as<IdType>();
	product.category_id = row[CATEGORY_ID_FIELD].as<IdType>();
	product.name = row[NAME_FIELD].as<std::string>();
	product.price = row[PRICE_FIELD].as<Money>();
	product.amount = row[AMOUNT_FIELD].as<int>();
	product.product_priority = row[PRODUCT_PRIORITY_FIELD].as<int>();
	product.is_bought = row[IS_BOUGHT_FIELD].as<bool>();
	product.add_date = row[ADD_DATE_FIELD].as<Timestamp>();

	if (row[PURCHASE_DATE_FIELD].is_null())
	{
		product.purchase_date = std::nullopt;
	}
	else
	{
		product.purchase_date = row[PURCHASE_DATE_FIELD].as<Timestamp>();
	}

	if (row[BUY_UNTIL_DATE_FIELD].is_null())
	{
		product.purchase_date = std::nullopt;
	}
	else
	{
		product.purchase_date = row[BUY_UNTIL_DATE_FIELD].as<Timestamp>();
	}

	return product;
}
