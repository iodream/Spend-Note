#include <QJsonArray>

#include "GetBalanceHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Logger/ScopedLogger.h"


GetBalanceHandler::GetBalanceHandler()
{
}

Net::Response GetBalanceHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	Q_UNUSED(request);

	auto user_id = std::get<long long>(m_params.Get(Params::USER_ID));
	Balance balance;

	balance.balance = m_facade->CalculateBalanceForUser(user_id);
	balance.planned_balance = m_facade->CalculatePlannedBalanceForUser(user_id);
	return FormJSONResponse(m_formatter.Format(balance));
}
