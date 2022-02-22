#include "ListRepository.h"

#include "Exceptions/NonexistentResource.h"
#include "DatabaseNames.h"

namespace db
{

ListRepository::ListRepository(pqxx::connection& db_connection) : m_db_connection(db_connection)
{
}


std::optional<IdType> ListRepository::AddList(const List& list)
{
	try
	{
		pqxx::work w{m_db_connection};
		pqxx::result id_rows = w.exec(
			"INSERT INTO " + db::list::TABLE_NAME + " ( " +
				db::list::USER_ID + ", " +
				db::list::STATE_ID + ", " +
				db::list::NAME + ") " +
			"VALUES (" +
				w.quote(list.owner_id) + ", " +
				w.quote(list.state_id) + ", " +
				w.quote(list.name) + ")" +
			" RETURNING " + db::list::ID + ";");

		w.commit();

		auto id_row = id_rows.front();
		return id_row[db::list::ID].as<IdType>();
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
		auto result = w.exec(
			"SELECT " + db::list::ID +
			" FROM  " + db::list::TABLE_NAME +
			" WHERE " + db::list::ID + " = " + w.quote(list_id));
		if (result.empty())
		{
			return false;
		}
		w.exec0(
			"DELETE FROM " + db::list::TABLE_NAME +
			" WHERE " + db::list::ID + " = " + w.quote(list_id) + ";");
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
			"SELECT " + db::list::ID +
			" FROM " + db::list::TABLE_NAME +
			" WHERE " +
				db::list::ID +" = "  + w.quote(list_id) + " AND " +
				db::list::USER_ID +" = "  + w.quote(user_id));

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
		pqxx::result list =  w.exec(
			"SELECT * FROM " + db::list::TABLE_NAME +
			" WHERE " + db::list::ID + " = " + w.quote(list_id) + ";");

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

		auto result = w.exec(
			"SELECT " + db::list::ID +
			" FROM  " + db::list::TABLE_NAME +
			" WHERE " + db::list::ID + " = " + w.quote(list.id));

		if (result.empty())
		{
			return false;
		}

		w.exec0(
			"UPDATE " + db::list::TABLE_NAME +
			" SET " +
				db::list::STATE_ID + " = " + w.quote(list.state_id) + ", " +
				db::list::NAME + " = " + w.quote(list.name) +
			" WHERE " + db::list::ID + " = " + w.quote(list.id) + ";");

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

	list.id = row[db::list::ID].as<IdType>();
	list.owner_id = row[db::list::USER_ID].as<IdType>();
	list.state_id = row[db::list::STATE_ID].as<IdType>();
	list.name = row[db::list::NAME].as<std::string>();

	return list;
}

std::vector<List> ListRepository::GetAllLists(const IdType& user_id)
{
	std::vector<List> list;
	try
	{
		pqxx::work w{m_db_connection};

		pqxx::result user_ids = w.exec(
			"SELECT " + db::user::ID +
			" FROM " + db::user::TABLE_NAME +
			" WHERE " + db::user::ID + " = " + w.quote(user_id) + ";");
		if (user_ids.empty())
		{
			throw NonexistentResource("User with id = " + std::to_string(user_id) + " not found");
		}

		pqxx::result r = w.exec(
			"SELECT * FROM " + db::list::TABLE_NAME +
			" WHERE " + db::list::USER_ID + " = " + w.quote(user_id) + ";");
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

}
