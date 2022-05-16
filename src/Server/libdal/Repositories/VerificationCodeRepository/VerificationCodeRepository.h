#pragma once

#include <string>
#include <optional>
#include <pqxx/pqxx>
#include "DTOs/VerificationCode.h"

namespace db
{
class VerificationCodeRepository
{
public:
	VerificationCodeRepository(pqxx::connection& db_connection);

	std::optional<IdType> Add(const VerificationCode& code);
	std::optional<VerificationCode> GetById(IdType id);
	std::optional<VerificationCode> GetByUserId(IdType user_id);
	bool Update(const VerificationCode& code);
	bool Remove(IdType id);
private:
	static VerificationCode VerificationCodeFromRow(const pqxx::row& row);

	pqxx::connection& m_database_connection;
};
}
