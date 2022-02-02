#pragma once

#include <string>

#include "../AuthorizedHandler.h"
#include "../libdal/Facade/IDbFacade.h"

class AddIncomeHandler : public AuthorizedHandler
{
	class JSONParser
	{
	public:
		Income Parse(const QJsonDocument& json_doc);
	};

	class JSONFormatter
	{
	public:
		struct DTO
		{
			IdType income_id;
		};

		QJsonDocument Format(const DTO& dto);
	};

public:
	AddIncomeHandler();
	virtual ~AddIncomeHandler() override {};

	Net::Response AuthHandle(const Net::Request& request) override;

	JSONParser m_parser{};
	JSONFormatter m_formatter{};
};
