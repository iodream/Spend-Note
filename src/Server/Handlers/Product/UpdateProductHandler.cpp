#include <QJsonObject>

#include "UpdateProductHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Utils.h"

#include "../libdal/Exceptions/SQLFailure.h"

ChangeProductHandler::ChangeProductHandler(IDbFacade::Ptr facade)
	: AuthorizedHandler(std::move(facade))
{
}

Product ChangeProductHandler::JSONParser::Parse(const QJsonObject &payload)
{
    auto json = payload;
	return ParseProduct(json);
}

Net::Response  ChangeProductHandler::AuthHandle(const Net::Request &request)
{
	if(request.method == Net::HTTP_METHOD_PUT)
	{
		auto json = request.json_payload;
        try
		{
            if(m_facade->UpdateProduct(m_parser.Parse(json.object())))
            {
				return FormEmptyResponse();
			}
			else
            {
                return FormErrorResponse(
                    NetError::Status::HTTP_NOT_FOUND,
                    "Resource not found");
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
