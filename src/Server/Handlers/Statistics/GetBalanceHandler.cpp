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

	if (request.uid != user_id){
		return FormErrorResponse(
			NetError::Status::HTTP_FORBIDDEN,
			"User with id \"" + std::to_string(request.uid) +
			"\" can't get balance for user with id \"" + std::to_string(user_id) + "\"");
	}

	Balance balance;

	balance.balance = m_facade->CalculateBalanceForUser(user_id);
	balance.planned_balance = m_facade->CalculatePlannedBalanceForUser(user_id);
	return FormJSONResponse(m_formatter.Format(balance));
}
