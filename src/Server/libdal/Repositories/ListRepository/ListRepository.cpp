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


std::optional<IdType> ListRepository::AddList(const List& list)
{
	try
	{
		pqxx::work w{m_db_connection};
		pqxx::result id_rows = w.exec(
					"INSERT INTO " + TABLE_NAME + " ( " +
					USER_ID + ", " +
					LIST_STATE_ID + ", " +
					LIST_NAME + ") " +
					"VALUES (" +
					w.quote(list.owner_id) + ", " +
					w.quote(list.state_id) + ", " +
					w.quote(list.name) + ")" +
					" RETURNING " + ID_FIELD + ";");

		w.commit();

		auto id_row = id_rows.front();
		return id_row[ID_FIELD].as<IdType>();
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
	return std::nullopt;
}


bool ListRepository::Remove(const IdType& list_id)
{
	try
	{
		pqxx::work w{m_db_connection};
		auto result = w.exec("SELECT " + ID_FIELD + " FROM  " + TABLE_NAME + " WHERE " + ID_FIELD + " = " + w.quote(list_id));
		if (result.empty())
		{
			return false;
		}
		w.exec0("DELETE FROM " + TABLE_NAME + " WHERE " + ID_FIELD + " = " + w.quote(list_id) + ";");
		w.commit();
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
	return true;
}

bool ListRepository::CanUserEditList(IdType user_id, IdType list_id)
{
	try
	{
		pqxx::nontransaction w{m_db_connection};

		auto result = w.exec(
			"SELECT " + ID_FIELD +
			" FROM " + TABLE_NAME +
			" WHERE " +
				ID_FIELD +" = "  + w.quote(list_id) + " AND " +
				USER_ID +" = "  + w.quote(user_id));

		if (result.empty())
		{
			return false;
		}
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}

	return true;
}


std::optional<List> ListRepository::GetList(const IdType& list_id)
{
	try
	{
		pqxx::work w{m_db_connection};
		pqxx::result list =  w.exec("SELECT * FROM " + TABLE_NAME + " WHERE " + ID_FIELD + " = " + w.quote(list_id) + ";");

		if(!list.empty())
		{
			return ParseSQLRow(list.front());
		}
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
	return std::nullopt;
}


bool ListRepository::Update(const List& list)
{
	try
	{
		pqxx::work w{m_db_connection};
		auto result = w.exec("SELECT " + ID_FIELD + " FROM  " + TABLE_NAME + " WHERE " + ID_FIELD + " = " + w.quote(list.list_id));
		if (result.empty())
		{
			return false;
		}
		w.exec0("UPDATE " + TABLE_NAME + " SET " + LIST_STATE_ID + " = " + w.quote(list.state_id) + ", "
				+ LIST_NAME + " = " + w.quote(list.name) + " WHERE " + ID_FIELD + " = " + w.quote(list.list_id) + ";");

		w.commit();
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
	return true;
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

std::vector<List> ListRepository::GetAllLists(const IdType& user_id)
{
    std::vector<List> list;
    try
	  {
		pqxx::work w{m_db_connection};

		pqxx::result r = w.exec("SELECT * FROM " + TABLE_NAME + " WHERE " + USER_ID + " = " + w.quote(user_id) + ";");

		for(const auto& row : r)
		{
			list.push_back(ParseSQLRow(row));
		}
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
    return list;
}
