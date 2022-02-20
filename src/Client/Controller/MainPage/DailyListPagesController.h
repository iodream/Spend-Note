#include "Controller/HTTPClient.h"

#include "View/MainPage/DailyList/DailyListSubPage/DailyListSubPage.h"
#include "View/Constants.h"

#include "Entities/PageData.h"

class DailyListPagesController : public QObject
{
	Q_OBJECT
public:
	explicit DailyListPagesController(
		HTTPClient& http_client,
		std::string& hostname,
		IdType& user_id,
		DailyListSubPage& dailylists_page);

	virtual ~DailyListPagesController() override {}

	bool UpdateDailyListPage();
private:
	void ConnectDailyListPage();

	HTTPClient& m_http_client;
	std::string& m_hostname;
	IdType& m_user_id;

	DailyListSubPage& m_daily_list_page;

signals:
	void Message(const QString& window_name, const QString& message);
	void ChangeSubPage(MainSubPages page, PageData data=PageData{});
	void UpdatePage(MainSubPages page, PageData data=PageData{});

	void GoBack(int n=1);

public slots:
	void OnGoToViewProduct(const Product& product);
};
