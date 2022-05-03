#pragma once

#include <string>

class EmailSender
{
public:
	EmailSender() = default;
	~EmailSender() = default;
	void SendEmail (const std::string& recipient, const std::string& code);
};
