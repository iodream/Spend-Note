#pragma once

#include <string>
#include <memory>
#include "Types.h"

#include "ICommandHandler.h"

class LoginHandler : public ICommandHandler
{
	class JSONFormatter
	{
	public:
		struct OutDto {
			std::string token;
			db::IdType id;
		};

		QJsonDocument Format(const OutDto& dto);
	};
	class JSONParser
	{
	public:
		struct Login{
			std::string email;
			std::string password;
			std::string password_hash;
			std::string salt;
		};
	Login Parse(const QJsonDocument& payload);

	};
private:
	void UpdatePeriodicIncomes(db::IdType user_id);
	void UpdatePeriodicProducts(db::IdType user_id);

public:
	LoginHandler();
	virtual ~LoginHandler() override {}

	Net::Response Handle(Net::Request& request) override;

	JSONFormatter m_formatter{};
	JSONParser m_parser{};
};
