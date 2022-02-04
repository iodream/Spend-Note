#pragma once

#include <QJsonObject>

#include "../libdal/Facade/IDbFacade.h"

db::Product ParseProduct(const QJsonObject& json);
