#include "AddIncomeCategoryHandler.h"

Net::Response AddIncomeCategoryHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	auto user_id = std::get<long long>(m_params.Get(Params::USER_ID));
	auto income_category = m_parser.Parse(request.json_payload.object());

	auto db_income_category = ToDBIncomeCategory(income_category, user_id);

	IncomeCategoryId income_category_id;
	try
	{
		income_category_id.id = m_facade->AddIncomeCategory(db_income_category).value();
	}
	catch (const db::SQLFailure& ex)
	{
		return FormErrorResponse(
			NetError::Status::HTTP_CONFLICT,
			"Unable to create resource");
	}
	return FormJSONResponse(
		m_formatter.Format(income_category_id),
		Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_CREATED);
}
