#pragma once

#include <string>

#include "VerificationCodeFormatter.h"

#include "Poco/Net/MailMessage.h"
#include "Poco/Net/MailRecipient.h"
#include "Poco/Net/SecureSMTPClientSession.h"
#include "Poco/Net/StringPartSource.h"
#include "Poco/Net/SSLManager.h"
#include "Poco/Net/KeyConsoleHandler.h"
#include "Poco/Net/ConsoleCertificateHandler.h"
#include "Poco/SharedPtr.h"
#include "Poco/Path.h"
#include "Poco/Exception.h"
#include <iostream>


using Poco::Net::MailMessage;
using Poco::Net::MailRecipient;
using Poco::Net::SMTPClientSession;
using Poco::Net::SecureSMTPClientSession;
using Poco::Net::StringPartSource;
using Poco::Net::SSLManager;
using Poco::Net::Context;
using Poco::Net::KeyConsoleHandler;
using Poco::Net::PrivateKeyPassphraseHandler;
using Poco::Net::InvalidCertificateHandler;
using Poco::Net::ConsoleCertificateHandler;
using Poco::SharedPtr;
using Poco::Path;
//using Poco::Exception;

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

class SSLInitializer
{
public:
  SSLInitializer()
  {
  Poco::Net::initializeSSL();
  }

  ~SSLInitializer()
  {
  Poco::Net::uninitializeSSL();
  }
};
