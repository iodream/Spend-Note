#include "VerificationCodeRepository.h"

#include "Exceptions/DatabaseFailure.h"
#include "DatabaseNames.h"

namespace db
{

VerificationCodeRepository::VerificationCodeRepository(pqxx::connection &db_connection) :
		m_database_connection(db_connection)
{

}

std::optional<IdType> VerificationCodeRepository::Add(const VerificationCode &code)
{
	try
	{
		pqxx::work w(m_database_connection);
		auto id_rows = w.exec(
			"INSERT INTO " + verificationCode::TABLE_NAME + " (" +
				verificationCode::USER_ID + ", " +
				verificationCode::CODE + ", " +
				verificationCode::EXPIRATION_TIME +
			") VALUES (" +
				w.quote(code.user_id) + ", " +
				w.quote(code.code) + ", " +
				w.quote(code.expiration_time) + ")" +
			" RETURNING " + verificationCode::ID + ";");

		w.commit();

		auto id_row = id_rows.front();
		return id_row[verificationCode::ID].as<IdType>();
	}

	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}

	return std::nullopt;
}

std::optional<VerificationCode> VerificationCodeRepository::GetById(IdType id)
{
	try
	{
		pqxx::nontransaction w(m_database_connection);
		pqxx::result user_rows = w.exec(
			"SELECT " +
				verificationCode::ID + ", " +
				verificationCode::USER_ID + ", " +
				verificationCode::CODE + ", " +
				verificationCode::EXPIRATION_TIME +
			" FROM " + verificationCode::TABLE_NAME +
			" WHERE " + verificationCode::ID + " = " + w.quote(id) + ";");

		if (!user_rows.empty())
		{
			return VerificationCodeFromRow(user_rows.front());
		}
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}

	return std::nullopt;
}

std::optional<VerificationCode> VerificationCodeRepository::GetByUserId(IdType user_id)
{
	try
	{
		pqxx::nontransaction w(m_database_connection);
		pqxx::result user_rows = w.exec(
			"SELECT " +
				verificationCode::ID + ", " +
				verificationCode::USER_ID + ", " +
				verificationCode::CODE + ", " +
				verificationCode::EXPIRATION_TIME +
			" FROM " + verificationCode::TABLE_NAME +
			" WHERE " + verificationCode::USER_ID + " = " + w.quote(user_id) + ";");

		if (!user_rows.empty())
		{
			return VerificationCodeFromRow(user_rows.front());
		}
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}

	return std::nullopt;
}

bool VerificationCodeRepository::Update(const VerificationCode& code)
{
	try
	{
		pqxx::work w(m_database_connection);

		auto result = w.exec(
			"SELECT " + verificationCode::ID +
			" FROM  " + verificationCode::TABLE_NAME +
			" WHERE " + verificationCode::ID + " = " + w.quote(code.id));
		if (result.empty())
		{
			return false;
		}

		w.exec0(
			"UPDATE " + verificationCode::TABLE_NAME +
			" SET " +
				verificationCode::USER_ID + " = " + w.quote(code.user_id) + ", " +
				verificationCode::CODE + " = " + w.quote(code.code) + ", " +
				verificationCode::EXPIRATION_TIME + " = " + w.quote(code.expiration_time) +
			" WHERE " + verificationCode::ID + " = " + w.quote(code.id) + ";");
		w.commit();
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
	return true;
}

bool VerificationCodeRepository::Remove(IdType id)
{
	try
	{
		pqxx::work w(m_database_connection);
		auto result = w.exec(
			"SELECT " + verificationCode::ID +
			" FROM  " + verificationCode::TABLE_NAME +
			" WHERE " + verificationCode::ID + " = " + w.quote(id));
		if (result.empty())
		{
			return false;
		}
		w.exec0("DELETE FROM " + verificationCode::TABLE_NAME + " WHERE " + verificationCode::ID + " = " + w.quote(id) + ";");
		w.commit();
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
	return true;
}

VerificationCode VerificationCodeRepository::VerificationCodeFromRow(const pqxx::row& row)
{
	VerificationCode code;
	code.id = row[verificationCode::ID].as<IdType>();
	code.user_id = row[verificationCode::USER_ID].as<IdType>();
	code.code = row[verificationCode::CODE].as<std::string>();
	code.expiration_time = row[verificationCode::EXPIRATION_TIME].as<Timestamp>();
	return code;
}

}
