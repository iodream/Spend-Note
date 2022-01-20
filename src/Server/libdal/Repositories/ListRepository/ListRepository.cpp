#include "ListRepository.h"

namespace
{
	const std::string& TABLE_NAME = "List";
	const std::string& ID_FIELD = "id";
	const std::string& USER_ID = "userId";
	const std::string& LIST_NAME = "name";
	const std::string& LIST_STATE_ID = "stateId";
	const std::string& TABLE_WITH_CATEGORY = "ListState";
}


ListRepository::ListRepository(pqxx::connection& db_connection) : m_db_connection(db_connection)
{
}


void ListRepository::AddList(const List& list)
{
	try
	{
		pqxx::work w{m_db_connection};
		w.exec0("INSERT INTO " + TABLE_NAME + " ( " +  USER_ID + ", " + LIST_STATE_ID + ", " + LIST_NAME + ") "
				+ "VALUES (" + w.quote(list.owner_id) + ", " + w.quote(list.state_id) + ", " + w.quote(list.name) + ");");

		w.commit();
	}
	catch(const pqxx::pqxx_exception& e)
	{
		throw DatabaseFailure();
	}
}


void ListRepository::Remove(const IdType& list_id)
{
	try
	{
		pqxx::work w{m_db_connection};
		w.exec0("DELETE FROM " + TABLE_NAME + " WHERE " + ID_FIELD + " = " + w.quote(list_id) + ";");
		w.commit();
	}
	catch(const pqxx::pqxx_exception& e)
	{
		throw DatabaseFailure();
	}
}


std::optional<List> ListRepository::GetList(const IdType& list_id)
{
	try
	{
		pqxx::work w{m_db_connection};
		pqxx::row list =  w.exec1("SELECT * FROM " + TABLE_NAME + " WHERE " + ID_FIELD + " = " + w.quote(list_id));

		if(!list.empty())
		{
			return ParseSQLRow(list);
		}
	}
	catch(const pqxx::pqxx_exception& e)
	{
		throw DatabaseFailure();
	}
	return std::nullopt;
}


void ListRepository::Update(const List& list)
{
	try
	{
		pqxx::work w{m_db_connection};
		w.exec0("UPDATE " + TABLE_NAME + " SET " + LIST_STATE_ID + " = " + w.quote(list.state_id) + ", "
				+ LIST_NAME + " = " + w.quote(list.name) + " WHERE " + ID_FIELD + " = " + w.quote(list.list_id) + ";");

		w.commit();
	}
	catch(const pqxx::pqxx_exception& e)
	{
		throw DatabaseFailure();
	}
}

List ListRepository::ParseSQLRow(const pqxx::row &row)
{
	List list;

	list.list_id = row[ID_FIELD].as<IdType>();
	list.owner_id = row[USER_ID].as<IdType>();
	list.state_id = row[LIST_STATE_ID].as<IdType>();
	list.name = row[LIST_NAME].as<std::string>();

	return list;
}

std::optional<std::vector<List>> ListRepository::GetAllLists(const IdType& user_id)
{
	try
	{
		pqxx::work w{m_db_connection};
		std::vector<List> list;

		auto number_of_rows = w.exec("SELECT FROM " + TABLE_NAME + " WHERE " + USER_ID + " = " + w.quote(user_id) + ";");
		pqxx::result r = w.exec_n(number_of_rows.size(),
									"SELEC * FROM " + TABLE_NAME + " WHERE " + USER_ID + " = " + w.quote(user_id) + ";");

		for(const auto& row : r)
		{
			list.push_back(ParseSQLRow(row));
		}
		return list;
	}
	catch(const pqxx::pqxx_exception& e)
	{
		throw DatabaseFailure();
	}
	return std::nullopt;
}
