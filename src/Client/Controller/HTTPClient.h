#pragma once

#include <string>

#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPClientSession.h>

#include "Net/Constants.h"
#include "Net/Message.h"

class HTTPClient
{
public:
	HTTPClient() {}
	void set_token(const std::string& str_token);
	void set_auth_scheme(const std::string& str_auth_scheme);
	void ReleaseToken();
	Net::Response Request(const Net::Request& net_request);
private:
	void AddCredentials (Poco::Net::HTTPRequest& request);
	void SendRequest(
		Poco::Net::HTTPRequest& request,
		Poco::Net::HTTPClientSession& session,
		const Net::Request& net_request);
	Net::Response FormResponse(
		const Poco::Net::HTTPResponse& response,
		std::istream& received_stream);
private:
	std::string m_token;
	Net::AuthSchemeType m_auth_scheme;
};
