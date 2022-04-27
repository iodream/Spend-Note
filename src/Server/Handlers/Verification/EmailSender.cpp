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

#include "EmailSender.h"
#include "SSLInitializer.h"

void EmailSender::SendEmail(const std::string& recipient, const std::string& code)
{
	  SSLInitializer sslInitializer;

	  // Note: we must create the passphrase handler prior Context
	  SharedPtr<InvalidCertificateHandler> pCert = new ConsoleCertificateHandler(false); // ask the user via console
	  Context::Ptr pContext = new Context(Context::CLIENT_USE, "", "", "", Context::VERIFY_RELAXED, 9, true, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
	  SSLManager::instance().initializeClient(0, pCert, pContext);

	  MailMessage message;
	  message.setSender(sender);
	  message.addRecipient(MailRecipient(MailRecipient::PRIMARY_RECIPIENT, recipient));
	  message.setSubject("Hello from the POCO C++ Libraries");
	  std::string content;
	  content += code;
	  content += "\n";
	  content += recipient;
	  content += ",\r\n\r\n";
	  content += "Demo messages.\r\n\r\n";
	  message.setContent(content);

	  SecureSMTPClientSession session(mailhost);
	  session.login();
	  session.startTLS(pContext);
	  if (!username.empty())
	  {
		session.login(SMTPClientSession::AUTH_LOGIN, username, password);
	  }
	  session.sendMessage(message);
	  session.close();
}
