#pragma once

#include "../../AuthorizedHandler.h"
#include "../libdal/Facade/IDbFacade.h"
#include "../DTO/IncomeIn.h"

class IncomeJSONParser
{	
public:
	Income Parse(const QJsonDocument& json_doc);
private:
	Income ToIncome(const IncomeIn& income_in);
};
