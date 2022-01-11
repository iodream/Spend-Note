#pragma once

#include <string>

#include <Poco/Net/HTTPRequest.h>
#include <Poco/URI.h>
#include <Poco/Net/HTTPClientSession.h>
#include "Net/Message.h"

class HTTPClient
{
public:
    HTTPClient(){};
    void set_token(const std::string& str_token);
    Net::Response Request(const Net::Request& net_request);
    void SendRequest(Poco::Net::HTTPRequest& request,
                     Poco::Net::HTTPClientSession& session,
                     const Net::Request& net_request);
    Net::Response FormResponse(const Poco::Net::HTTPResponse& response,
                                  std::istream &received_stream);
private:
    std::string m_token;
};
