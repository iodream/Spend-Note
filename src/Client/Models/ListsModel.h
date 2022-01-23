#pragma once

#include <QJsonDocument>
#include <QJsonObject>
#include <QCryptographicHash>

#include "DTO/List.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class ListsModel
{
public:
	class JSONFormatter
	{
	public:
		QJsonDocument Format(const ListInDTO& dto);
	};

	class JSONParser
	{
	public:
		void Parse(QJsonObject json, ListOutDTO& dto);
	};

	Net::Request FormRequest(ListInDTO dto);
	ListOutDTO  ParseResponse(const Net::Response& response);

	JSONParser m_parser{};
	JSONFormatter m_formatter{};
};
//make fascade to contain lost of other logic for lists identical as server
