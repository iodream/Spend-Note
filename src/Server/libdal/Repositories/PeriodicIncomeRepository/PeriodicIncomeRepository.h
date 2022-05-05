#pragma once

#include <string>
#include <optional>
#include <pqxx/pqxx>
#include "DTOs/PeriodicIncome.h"
#include "DTOs/PeriodType.h"

namespace db
{

class PeriodicIncomeRepository
{
public:
	PeriodicIncomeRepository(pqxx::connection& db_connection);

	std::optional<IdType> Add(const PeriodicIncome& income);
	std::optional<PeriodicIncome> GetById(IdType id);
	std::vector<PeriodicIncome> GetAllIncomes(IdType user_id);

	bool Update(const PeriodicIncome& product);
	bool Remove(IdType id);

	bool CanUserEditIncome(IdType user_id, IdType income_id);

	std::vector<PeriodType> GetAllPeriodTypes();
	bool CanGenerate(IdType periodic_id);
	bool UpdateAddNext(const PeriodicIncome& income);
private:
	static PeriodicIncome IncomeFromRow(const pqxx::row& row);
	static PeriodType PeriodFromRow(const pqxx::row& row);
	std::string PeriodIdToString(IdType id);

	pqxx::connection& m_database_connection;
};
}
