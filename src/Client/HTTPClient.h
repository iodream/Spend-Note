#pragma once

#include <string>

#include <Poco/Net/HTTPRequest.h>

#include "Net/Message.h"

class HTTPClient
{
public:
    HTTPClient(){};
    void setToken(const std::string& str_token);
    Net::Response SendRequest(const Net::Request& net_request);
    Poco::Net::HTTPRequest getJsonRequest(const Net::Request& net_request);
    Net::Response getNetResponse(const Poco::Net::HTTPResponse& response,
                                  std::istream &received_stream);
private:
    std::string m_token;
};
