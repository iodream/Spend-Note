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
