#pragma once

#include <QJsonObject>

#include "../libdal/Facade/IDbFacade.h"

Product ParseProduct(const QJsonObject& json);
