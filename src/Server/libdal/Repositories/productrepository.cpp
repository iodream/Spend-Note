#include "productrepository.h"

#include <algorithm>
#include "Types.h"
#include "Exceptions/databasefailure.h"

namespace
{
	const std::string& TABLE_NAME = "Product";
	const std::string& ID_FIELD = "id";
	const std::string& LIST_ID_FIELD = "listId";
	const std::string& CATEGORY_ID_FIELD = "categoryId";
	const std::string& NAME_FIELD = "name";
	const std::string& PRICE_FIELD = "price";
	const std::string& AMOUNT_FIELD = "amount";
	const std::string& PRODUCT_PRIORITY_FIELD = "productPriority";
	const std::string& IS_BOUGHT_FIELD = "isBought";
	const std::string& ADD_DATE_FIELD = "addDate";
	const std::string& PURCHASE_DATE_FIELD = "purchaseDate";
	const std::string& BUY_UNTIL_DATE_FIELD = "buyUntilDate";
}

ProductRepository::ProductRepository(pqxx::connection& db_connection) : m_database_connection(db_connection)
{

}

void ProductRepository::Add(const Product& product)
{
	pqxx::work w(m_database_connection);
	try
	{
		w.exec0(
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
					w.quote(product.buy_until_date) + ");");
		w.commit();
	}
	catch(const pqxx::pqxx_exception& e)
	{
		throw DatabaseFailure();
	}
}

std::optional<Product> ProductRepository::GetById(IdType id)
{
	pqxx::nontransaction w(m_database_connection);

	try
	{
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
	pqxx::nontransaction w(m_database_connection);
	std::vector<Product> products;

	try
	{
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

void ProductRepository::Update(const Product& product)
{
	pqxx::work w(m_database_connection);

	try
	{
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
}

void ProductRepository::Remove(IdType id)
{
	pqxx::work w(m_database_connection);

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
	product.purchase_date = row[PURCHASE_DATE_FIELD].get<Timestamp, std::optional>();
	product.buy_until_date = row[BUY_UNTIL_DATE_FIELD].get<Timestamp, std::optional>();
	return product;
}
