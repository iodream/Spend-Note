#pragma once

#include <QJsonDocument>
#include <QJsonObject>


#include "../../Entities/Parsers.h"
#include "../../Entities/Formatters.h"
#include "Net/Constants.h"
#include "Net/Message.h"


class AddNewListsModel
{
public:
	AddNewListsModel(const std::string& hostname) : m_hostname{hostname} {}
	Net::Request FormRequest(const List& list);
	ListId ParseResponse(const Net::Response& response);

private:
	const std::string& m_hostname;

	ListIdJSONParser m_parser;
	ListJSONFormatter m_formatter;
};

