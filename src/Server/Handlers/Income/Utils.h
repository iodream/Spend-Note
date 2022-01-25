#pragma once

#include <QJsonObject>


#include "../Income/AddIncomeHandler.h"
#include "../libdal/Facade/IDbFacade.h"


Income ParseIncome(const QJsonObject& json);
