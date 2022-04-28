#pragma once
#include <pqxx/pqxx>

#include "Types.h"
#include "DTOs/Product.h"


namespace db {
class RecommendationRepository
{
public:
	RecommendationRepository(pqxx::connection& db_connection);
	Product GetRecommendation(const IdType& user_id);


private:
	pqxx::connection& m_db_connection;
	Money GetUserBalance(IdType user_id, pqxx::work& work);
	bool DoesUserExist(IdType user_id, pqxx::work& work);
	Product ProductFromRow(const pqxx::row& row);
};
}
