#include "RemoveIncomeCategoryHandler.h"

Net::Response RemoveIncomeCategoryHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	auto income_category_id = std::get<long long>(m_params.Get(Params::INCOME_CATEGORY_ID));

	if (!m_facade->GetProductCategoryById(income_category_id))
		return FormErrorResponse(
			NetError::Status::HTTP_NOT_FOUND,
			"Resource not found");

	if (!m_facade->CanUserEditProductCategory(request.uid, income_category_id))
		return FormErrorResponse(
			NetError::Status::HTTP_FORBIDDEN,
			"Remove product category with id \"" + std::to_string(income_category_id) + "\" is forbidden");

	m_facade->RemoveProductCategory(income_category_id);
	return FormEmptyResponse();
}
