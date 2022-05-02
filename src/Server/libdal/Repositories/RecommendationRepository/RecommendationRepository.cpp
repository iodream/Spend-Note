#include "RecommendationRepository.h"

#include "Exceptions/NonexistentResource.h"
#include "DatabaseNames.h"
#include <random>


namespace db {

RecommendationRepository::RecommendationRepository(pqxx::connection& db_connection) : m_db_connection(db_connection)
{
}

std::optional<Product> RecommendationRepository::GetRecommendation(const IdType &user_id)
{
	try
	{
		pqxx::work w{m_db_connection};
		if (DoesUserExist(user_id, w))
		{
			throw NonexistentResource("User with id = " + std::to_string(user_id) + " not found");
		}
		pqxx::result rec_product_rows = w.exec(
				"SELECT * FROM " + db::product::TABLE_NAME +
				" JOIN " + db::list::TABLE_NAME + " ON " + product::LIST_ID + " =  " + list::TABLE_NAME + "." + list::ID +
				" WHERE " + db::list::USER_ID + " = " + w.quote(user_id) +
				" AND " + product::PRICE + " < " + w.quote(GetUserBalance(user_id, w)) +
				" AND " + product::IS_BOUGHT + " = " + w.quote(false) +
				" AND " + product::BUY_UNTIL_DATE + " < NOW()" + ";"); // <

		if (!rec_product_rows.empty())
		{
			std::random_device random_device;
			std::mt19937 engine{random_device()};
			std::uniform_int_distribution<> dist(0, rec_product_rows.size() - 1);
			auto random_number = dist(engine);
			return ProductFromRow(rec_product_rows[random_number]);
		}
		else
		{
			return std::nullopt;
		}
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
}

Money RecommendationRepository::GetUserBalance(IdType user_id, pqxx::work& work)
{
	try
	{
		auto total_income_row = work.exec1(
			"SELECT COALESCE(SUM(" + db::income::AMOUNT + "), 0) " +
			"FROM " + db::income::TABLE_NAME +
			" WHERE " +
				db::income::USER_ID + " = " + work.quote(user_id) + " AND " +
				db::income::EXPIRATION_TIME + " > LOCALTIMESTAMP" + ";");

		auto total_outcome_row = work.exec1(
			"SELECT COALESCE(SUM(" + db::product::AMOUNT + " * " + db::product::PRICE + "), 0) " +
			"FROM " + db::product::TABLE_NAME + " JOIN " + db::list::TABLE_NAME +
			" ON " + db::product::TABLE_NAME + "." + db::product::LIST_ID + " = " + db::list::TABLE_NAME + "." + db::list::ID +
			" WHERE " + db::list::USER_ID + " = " + work.quote(user_id) + " AND " + db::product::IS_BOUGHT + ";");

		return total_income_row.front().as<Money>() - total_outcome_row.front().as<Money>();
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
}

bool RecommendationRepository::DoesUserExist(IdType user_id, pqxx::work& work)
{
	pqxx::result user_ids = work.exec(
		"SELECT " + user::ID +
		" FROM " + user::TABLE_NAME +
		" WHERE " + user::ID + " = " + work.quote(user_id) + ";");
	return user_ids.empty();
}

Product RecommendationRepository::ProductFromRow(const pqxx::row& row)
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
