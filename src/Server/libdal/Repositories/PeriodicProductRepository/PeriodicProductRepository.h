#pragma once

#include <string>
#include <optional>
#include <pqxx/pqxx>
#include "DTOs/PeriodicProduct.h"
#include "DTOs/PeriodType.h"

namespace db
{
class PeriodicProductRepository
{
public:
	PeriodicProductRepository(pqxx::connection& db_connection);

	std::optional<IdType> Add(const PeriodicProduct& product);
	std::optional<PeriodicProduct> GetById(IdType id);
	std::vector<PeriodicProduct> GetByListId(IdType list_id);

	bool Update(const PeriodicProduct& product);
	bool Remove(IdType id);

	bool CanUserEditProduct(IdType user_id, IdType product_id);

	std::vector<PeriodType> GetAllPeriodTypes();
	bool CanGenerate(IdType periodic_id);
	bool UpdateAddNext(const PeriodicProduct& product);
	std::vector<PeriodicProduct> GetByUserId(IdType user_id);
private:
	static PeriodicProduct ProductFromRow(const pqxx::row& row);
	static PeriodType PeriodFromRow(const pqxx::row& row);
	std::string PeriodIdToString(IdType id);

	pqxx::connection& m_database_connection;
};
}
