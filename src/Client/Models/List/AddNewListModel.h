#pragma once

#include <QJsonDocument>
#include <QJsonObject>


#include "../../Entities/Parsers.h"
#include "../../Entities/Formatters.h"
#include "Net/Constants.h"
#include "Net/Message.h"
#include <string>

class AddNewListsModel
{
public:
	AddNewListsModel(const std::string& hostname) : m_hostname{hostname} {}
	Net::Request FormRequest(const List& list, const IdType& user_id);
	ListId ParseResponse(const Net::Response& response);
	bool CheckName(QString name);

private:
	const std::string& m_hostname;

	ListIdJSONParser m_parser;
	ListJSONFormatter m_formatter;
};

