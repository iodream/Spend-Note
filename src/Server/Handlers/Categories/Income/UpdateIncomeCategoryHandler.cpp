#include "UpdateIncomeCategoryHandler.h"

Net::Response UpdateIncomeCategoryHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;

	auto category_id = std::get<IdType>(m_params.Get(Params::INCOME_CATEGORY_ID));

	if(!m_facade->GetIncomeCategoryById(category_id))
		return FormErrorResponse(
			NetError::Status::HTTP_NOT_FOUND,
			"Resource not found");

	auto category = m_parser.Parse(request.json_payload.object());

	if (!m_facade->CanUserEditIncomeCategory(request.uid, category_id))
		return FormErrorResponse(
			NetError::Status::HTTP_FORBIDDEN,
			"Update Income category with id \"" + std::to_string(category_id) + "\" is forbidden");

	auto db_category = ToDBIncomeCategory(category, request.uid);
	m_facade->UpdateIncomeCategory(db_category);

	return FormEmptyResponse();
}
