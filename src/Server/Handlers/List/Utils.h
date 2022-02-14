#pragma once

#include "../libdal/Facade/IDbFacade.h"
#include "../Entities/Entities.h"

db::List ToDBList(const List& list);

List ToNetList(const db::List& db_list, const db::ListState& state);

ListState ToNetListState(const db::ListState& db_list_state);
