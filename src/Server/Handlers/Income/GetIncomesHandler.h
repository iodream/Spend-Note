#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"

#include "../Entities/Entities.h"
#include "../Entities/Formatters.h"

#include "../libdal/DTOs/Income.h"

class GetIncomesHandler : public AuthorizedHandler
{
public:
	GetIncomesHandler();
	virtual ~GetIncomesHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
private:
	IncomesJSONFormatter m_formatter;
	Income ToNetIncome(const db::Income& db_income, const db::IncomeCategory& category);
};
