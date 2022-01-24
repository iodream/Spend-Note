#include "ListsModel.h"
#include "Net/Parsing.h"

Net::Request ListsModel::FormRequest(ListInDTO dto)
{
	Net::Request request;
	request.uri = "http://localhost:8080/list/get_lists";
	request.method = Net::HTTP_METHOD_GET;
	request.content_type = Net::CONTENT_TYPE_APPLICATION_JSON;
	request.auth_scheme=Net::AUTH_SCHEME_TYPE_BEARER;

	//request.json_payload = m_formatter.Format(dto);
	return request;
}

QJsonDocument ListsModel::JSONFormatter::Format(const ListInDTO& dto)
{
//	QJsonObject json;
//	QByteArray password = QByteArray::fromStdString(dto.password);

//	json["login"] = dto.login.c_str();
//	auto digest = QString(QCryptographicHash::hash(
//			password, QCryptographicHash::Sha1).toHex());
//	json["password"] = digest.toStdString().c_str();
//    return QJsonDocument(json);
}

void ListsModel::JSONParser::Parse(QJsonObject json, ListOutDTO& dto)
{
	SafeReadArray(json, "lists", dto.data);
	//add parsing of array
}

ListOutDTO ListsModel::ParseResponse(const Net::Response& response)
{
	ListOutDTO dto;

	m_parser.Parse(response.json_payload.object(), dto);

	return dto;
}
