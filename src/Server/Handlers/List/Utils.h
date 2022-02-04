#pragma once

#include <QJsonObject>

#include "../libdal/Facade/IDbFacade.h"

db::List ParseList(const QJsonObject& json);
