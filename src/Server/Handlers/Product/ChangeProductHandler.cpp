#include <QJsonObject>
#include <memory>
#include <optional>

#include "QJsonObject"
#include "QJsonArray"


#include "ChangeProductHandler.h"
#include "Common.h"
#include "Net/Parsing.h"
#include "../libdal/Facade/DbFacade.h"
#include "../libdal/DTOs/Product.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "Product/Utils.h"

#include "../libdal/Exceptions/SQLFailure.h"

ChangeProductHandler::ChangeProductHandler(IDbFacade::Ptr facade)
	: AuthorizedHandler(std::move(facade))
{
}

ChangeProductHandler::JSONParser::DTO ChangeProductHandler::JSONParser::Parse(const QJsonDocument &payload)
{
	auto json = payload.object();
	return ParseProduct(json);
}

Net::Response  ChangeProductHandler::AuthHandle(const Net::Request &request)
{
	if(request.method == Net::HTTP_METHOD_PUT)
	{
		auto json = request.json_payload;
		try
		{
			if(m_facade->UpdateProduct(m_parser.Parse(json))){
				return FormEmptyResponse();
			}
			else
			{
				return FormErrorResponse(
					NetError::Status::HTTP_CONFLICT,
					"Unable to update resource");
			}
		}
		catch (const SQLFailure& ex) {
			return FormErrorResponse(
				NetError::Status::HTTP_CONFLICT,
				"Unable to update resource");
		}
	}
	return FormErrorResponse(
		NetError::Status::HTTP_BAD_REQUEST,
		"Unsupported method"
		);
}
