#pragma once

#include "Server/Handlers/AuthorizedHandler.h"
#include "ParsersAndFormatters/IncomeJSONFormatter.h"
#include "DTO/IncomeOut.h"

class GetIncomesHandler : public AuthorizedHandler
{
public:
	GetIncomesHandler(IDbFacade::Ptr facade);
	virtual Net::Response AuthHandle(const Net::Request& request) override;

private:
	Incomes Map(const std::vector<Income>& incomes);
	IncomeOut MapIncome(const Income& income);

	IncomeJSONFormatter m_formatter{};
};

