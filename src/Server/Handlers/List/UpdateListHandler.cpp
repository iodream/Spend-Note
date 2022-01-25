#include <QJsonDocument>

#include "UpdateListHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Utils.h"

#include "../libdal/Exceptions/SQLFailure.h"

List UpdateListHandler::JSONParser::Parser(const QJsonObject& payload)
{
    return ListParser(payload);
}

Net::Response UpdateListHandler::AuthHandle(const Net::Request &request)
{
    if(request.method == Net::HTTP_METHOD_PUT)
    {
        auto json = request.json_payload.object();
        try
        {
            if(m_facade->UpdateList(m_parser.Parser(json)))
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
