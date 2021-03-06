#include "Utils.h"

#include "Logger/ScopedLogger.h"

db::List ToDBList(const List& list)
{
	SCOPED_LOGGER;
	db::List db_list;
	db_list.id = list.id;
	db_list.name = list.name;
	db_list.owner_id = list.owner_id;
	db_list.state_id = list.state.id;
	return db_list;
}

List ToNetList(const db::List &db_list, const db::ListState& state)
{
	SCOPED_LOGGER;
	List list;
	list.id = db_list.id;
	list.name = db_list.name;
	list.owner_id = db_list.owner_id;
	list.state.id = state.id;
	list.state.name = state.name;

	return list;
}

ListState ToNetListState(const db::ListState& db_list_state)
{
	SCOPED_LOGGER;
	ListState list_state;
	list_state.id = db_list_state.id;
	list_state.name = db_list_state.name;
	return list_state;
}
