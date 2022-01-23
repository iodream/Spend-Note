#pragma once

#include <pqxx/pqxx>

#include "Types.h"
#include "Exceptions/DatabaseFailure.h"

class BalanceRepository
{
public:
	BalanceRepository(pqxx::connection& db_connection);

	Money CalculateBalance(IdType user_id);
	Money CalculatePlannedBalance(IdType user_id);
private:
	pqxx::connection& m_db_connection;
};
