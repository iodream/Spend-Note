#pragma once

#include <string>

#include "VerificationCodeFormatter.h"

class EmailSender
{
public:
	EmailSender() = default;
	~EmailSender() = default;
	void SendEmail (const std::string& recipient, const std::string& code);
private:
	const std::string mailhost = "smtp.gmail.com";
	const std::string sender = "SpendAndNote <spendandnote@gmail.com>";
	const std::string username = "spendandnote@gmail.com";
	const std::string password = "SpendAndNote123";
};


