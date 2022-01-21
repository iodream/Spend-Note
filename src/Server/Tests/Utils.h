#pragma once

#include <QJsonObject>

#include "../libdal/Facade/IDbFacade.h"

Product ReassembleProduct(const QJsonObject& json);
