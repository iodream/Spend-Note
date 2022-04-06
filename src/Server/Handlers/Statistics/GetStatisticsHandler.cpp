#include <QJsonArray>

#include "GetStatisticsHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Logger/ScopedLogger.h"
#include "Utils.h"
#include "../libdal/Exceptions/NonexistentResource.h"
#include "../Statistics/StatisticsFormatters/ExpensesPerCategoryFormatter.h"
#include "../Statistics/StatisticsFormatters/ExpensesPercentagePerCategoryFormatter.h"
#include "../Statistics/StatisticsFormatters/ExpensesPerDayFormatter.h"
#include "../Statistics/StatisticsFormatters/IncomesPerCategoryFormatter.h"
#include "../Statistics/StatisticsFormatters/IncomesPercentagePerCategoryFormatter.h"
#include "../Statistics/StatisticsFormatters/IncomesPerDayFormatter.h"

GetStatisticsHandler::GetStatisticsHandler()
{
}

Net::Response GetStatisticsHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	Q_UNUSED(request);

	auto user_id = std::get<long long>(m_params.Get(Params::USER_ID));

	if (request.uid != user_id){
		return FormErrorResponse(
			NetError::Status::HTTP_FORBIDDEN,
			"User with id \"" + std::to_string(request.uid) +
			"\" can't get expenses for user with id \"" + std::to_string(user_id) + "\"");
	}

	auto type_str = std::get<std::string>(m_params.Get(Params::STATISTICS_TYPE));
	auto period_str = std::get<std::string>(m_params.Get(Params::STATISTICS_PERIOD));
	auto format_str = std::get<std::string>(m_params.Get(Params::STATISTICS_FORMAT));

	auto type = ToType(type_str);
	auto period = ToPeriod(period_str);
	auto format = ToFormat(format_str);

	if (!type.has_value() || !period.has_value() || !format.has_value())
		return FormErrorResponse(NetError::Status::HTTP_BAD_REQUEST, "Uri parameters");

	if (type == Type::Incomes){
		if (format == Format::PerCategory)
			m_formatters_manager.set_formatter(new IncomesPerCategoryFormatter, std::move(m_facade));
		else if (format == Format::PercentagePerCategory)
			m_formatters_manager.set_formatter(new IncomesPercentagePerCategoryFormatter, std::move(m_facade));
		else
			m_formatters_manager.set_formatter(new IncomesPerDayFormatter, std::move(m_facade));
	}
	else {
		if (format == Format::PerCategory)
			m_formatters_manager.set_formatter(new ExpensesPerCategoryFormatter, std::move(m_facade));
		else if (format == Format::PercentagePerCategory)
			m_formatters_manager.set_formatter(new ExpensesPercentagePerCategoryFormatter, std::move(m_facade));
		else
			m_formatters_manager.set_formatter(new ExpensesPerDayFormatter, std::move(m_facade));
	}

	try {
		return FormJSONResponse (m_formatters_manager.ConcreteStatisticsFormat(user_id, period.value()));
	}
	catch (const db::NonexistentResource& ex) {
		return FormErrorResponse(NetError::Status::HTTP_NOT_FOUND, ex.what());
	}
}
