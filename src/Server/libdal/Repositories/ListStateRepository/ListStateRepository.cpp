#include "ListStateRepository.h"

namespace
{
	const std::string& TABLE_NAME = "ListState";
	const std::string& ID_FIELD = "id";
	const std::string& NAME_FIELD = "name";
}

ListStateRepository::ListStateRepository(pqxx::connection& db_connection) : m_db_connection(db_connection)
{
}

std::optional<ListState> ListStateRepository::GetById(const IdType &list_state_id)
{
	try
	{
		pqxx::work w{m_db_connection};
		pqxx::row list_state = w.exec1("SELECT * FROM " + TABLE_NAME + " WHERE " + ID_FIELD + " = " + w.quote(list_state_id) + ";");

		return ListState{list_state[ID_FIELD].as<IdType>(), list_state[NAME_FIELD].as<std::string>()};
	}
	catch(const pqxx::pqxx_exception& e)
	{
		throw DatabaseFailure();
	}
	return std::nullopt;
}

ListState ListStateRepository::ParseSQLRow(const pqxx::row &row)
{
	ListState list_state;

	list_state.list_state_id = row[ID_FIELD].as<IdType>();
	list_state.name = row[NAME_FIELD].as<std::string>();

	return list_state;
}

std::vector<ListState> ListStateRepository::GetAll()
{
	try
	{
		pqxx::work w{m_db_connection};
		std::vector<ListState> list_states;

		auto number_of_rows = w.exec("SELECT FROM " + TABLE_NAME + ";");
		pqxx::result r = w.exec_n(number_of_rows.size(), "SELECT * FROM " + TABLE_NAME + ";");

		for(const auto& row : r)
		{
			list_states.push_back(ParseSQLRow(row));
		}
		return list_states;
	}
	catch(const pqxx::pqxx_exception& e)
	{
		throw DatabaseFailure();
	}
}
