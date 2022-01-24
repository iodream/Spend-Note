#pragma once

#include <QJsonObject>

#include "../libdal/Facade/IDbFacade.h"

Income ParseIncome(const QJsonObject& json);
