#pragma once

#include <QString>
#include <QWidget>

#include "ListsItem.h"
#include "DTO/List.h"
#include <QJsonObject>

namespace Ui {
class ListsPage;
}

class ListsPage : public QWidget
{
	Q_OBJECT

public:
	using IdType = int;
	explicit ListsPage(QWidget *parent = nullptr);
	~ListsPage();
private:
	Ui::ListsPage *m_ui;
	int m_list_size;
signals:
	void SwitchPage();
	void GetLists();
public slots:
//	void UpdateData(ListOutDTO dto);
	void onSwitchPage();

};
