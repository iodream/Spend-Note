#include "HTTPClient.h"
#include <iostream>
#include <QJsonObject>
#include <QJsonDocument>
#include "Net/Constants.h"
int main()
{
    HTTPClient client;
    Net::Request net_request;
    net_request.uri = "http://localhost:8080/fake_login";
    net_request.method = Net::HTTP_METHOD_GET;
    net_request.content_type = Net::CONTENT_TYPE_APPLICATION_JSON;
    Net::Response net_response = client.SendRequest(net_request);
    std::cout << "Status: " << net_response.status << "\n";
    std::cout << "Reason: " << net_response.reason << "\n";

    QJsonObject json = net_response.json_playload.object();
    std::cout << "Token: " << json["token"].toString().toStdString() << "\n";

    return 0;
}
