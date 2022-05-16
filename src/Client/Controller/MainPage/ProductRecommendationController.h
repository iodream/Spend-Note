#pragma once

#include <QObject>

#include "Controller/HTTPClient.h"

#include "View/MainPage/MainPage.h"
#include "View/Constants.h"
#include "Entities/PageData.h"

class ProductRecommendationController : public QObject
{
	Q_OBJECT
public:
	explicit ProductRecommendationController(
		HTTPClient& http_client,
		std::string& hostname,
		IdType& user_id,
		MainPage& main_page
);

	virtual ~ProductRecommendationController() override {}
	bool UpdateRecommendations();

private:
	HTTPClient& m_http_client;
	std::string& m_hostname;
	IdType& m_user_id;
	MainPage& m_main_page;


signals:
	void ServerError(const int code, const std::string& desc);
	void ClientError(const QString& desc);
	void RecommendationClosed();
};
