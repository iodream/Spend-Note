#pragma once

#include <QString>
#include <QWidget>

namespace Ui {
class ListCreatePage;
}

class ListCreatePage : public QWidget
{
	Q_OBJECT

public:
	using IdType = int;
	explicit ListCreatePage(QWidget *parent=nullptr);
	~ListCreatePage();
signals:
	void GoBack();
public slots:
	void OnGoBackClicked();
private:

	Ui::ListCreatePage *m_ui;
	int m_list_size;
};
