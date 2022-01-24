#include "QJsonObject"

#include "Common.h"
#include "Net/Constants.h"

const char* EMPTY_C_STRING = "";
const std::string EMPTY_STD_STRING = std::string{};

Net::Response FormJSONResponse(
        QJsonDocument&& json_doc,
        Poco::Net::HTTPServerResponse::HTTPStatus status)
{
	Net::Response response;
	response.content_type = Net::CONTENT_TYPE_APPLICATION_JSON;
	response.json_payload = json_doc;
    response.status = status;
    return response;
}

Net::Response FormEmptyResponse(
    Poco::Net::HTTPServerResponse::HTTPStatus status)
{
    Net::Response response;
    response.content_type = Net::CONTENT_TYPE_EMPTY;
    response.status = status;
    return response;
}
