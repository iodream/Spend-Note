#include "QJsonObject"

#include "Common.h"
#include "Net/Constants.h"

Net::Response FormJSONResponse(
        QJsonDocument&& json_doc,
        Poco::Net::HTTPServerResponse::HTTPStatus status)
{
	Net::Response response;
	response.content_type = Net::CONTENT_TYPE_APPLICATION_JSON;
    response.json_playload = json_doc;
    response.status = status;
    return response;
}
