#include "Poco/Net/MailMessage.h"
#include "Poco/Net/MailRecipient.h"
#include "Poco/Net/SecureSMTPClientSession.h"
#include "Poco/Net/StringPartSource.h"
#include "Poco/Net/SSLManager.h"
#include "Poco/Net/KeyConsoleHandler.h"
#include "Poco/Net/ConsoleCertificateHandler.h"
#include "Poco/SharedPtr.h"
#include "Poco/Path.h"

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

#include "EmailSender.h"

void EmailSender::SendEmail(const std::string& recipient, const std::string& code)
{
	MailMessage message;
	message.setSender(sender);
	message.addRecipient(MailRecipient(MailRecipient::PRIMARY_RECIPIENT, recipient));
	message.setSubject("Hello from the Spend And Note Application");
	std::string content;
	content += code;

	message.setContent(content);

	SMTPClientSession session(mailhost);
	session.login();
	if (!username.empty())
	{
	  session.login(SMTPClientSession::AUTH_LOGIN, username, password);
	}
	session.sendMessage(message);
	session.close();
}
