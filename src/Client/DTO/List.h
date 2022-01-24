#pragma once

#include <QString>

#include "../Common.h"

struct List {
	IdType list_id;
	IdType owner_id;
	IdType state_id;
	QString name;
	QString state;
};
