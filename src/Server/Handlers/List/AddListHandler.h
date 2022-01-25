#pragma once

#include "../AuthorizedHandler.h"
#include "../libdal/DTOs/List.h"

class AddListHandler : public AuthorizedHandler
{
	class JSONParser
	{
	public:
		List Parse(const QJsonDocument& payload);
	};

	class JSONFormatter
	{
	public:
		struct DTO {
			IdType id;
		};

		QJsonDocument Format(const DTO& dto);
	};
public:
	AddListHandler(IDbFacade::Ptr facade);
	virtual ~AddListHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;

private:
	JSONFormatter m_formatter{};
	JSONParser m_parser{};
};
