#include <QJsonDocument>

#include "UpdateListHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "../Utils.h"

#include "../libdal/Exceptions/SQLFailure.h"

UpdateListHandler::JSONParser::DTO UpdateListHandler::JSONParser::Parser(const QJsonDocument &payload)
{
    DTO list;

    SafeReadId(payload.object(), "list_id", list.list_id);
    SafeReadId(payload.object(), "owner_id", list.owner_id);
    SafeReadId(payload.object(), "state_id", list.state_id);
    SafeReadString(payload.object(), "name", list.name);

    return list;
}

Net::Response UpdateListHandler::AuthHandle(const Net::Request &request)
{
    if(request.method == Net::HTTP_METHOD_PUT)
    {
        auto json = request.json_payload;
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
