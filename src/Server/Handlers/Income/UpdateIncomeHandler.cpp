#include <QJsonArray>
#include "UpdateIncomeHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Utils.h"
#include "../libdal/Exceptions/SQLFailure.h"
UpdateIncomeHandler::UpdateIncomeHandler(IDbFacade::Ptr facade)
    : AuthorizedHandler(std::move(facade))
{
}
UpdateIncomeHandler::JSONParser::DTO UpdateIncomeHandler::JSONParser::Parse(
    const QJsonDocument& payload)
{
    DTO dto;
    auto json = payload.object();
    return ParseIncome(json);
}

Net::Response UpdateIncomeHandler::AuthHandle(const Net::Request& request)
{
    if (request.method == Net::HTTP_METHOD_POST) {
        auto in_dto = m_parser.Parse(request.json_payload);
        try {
        m_facade->UpdateIncome(in_dto);
        return FormEmptyResponse();
        }
        catch(const DatabaseFailure& exception)
        {
            return FormErrorResponse(
                InternalError::Status::HTTP_INTERNAL_SERVER_ERROR,
                "Failed to retrieve incomes from database");
        }
    }
    return FormErrorResponse(
        NetError::Status::HTTP_BAD_REQUEST,
        "Unsupported method");
}
