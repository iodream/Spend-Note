#pragma once

#include <QString>
#include <QWidget>

#include "Client/Entities/Entities.h"
#include <QJsonObject>

#include "ListItem.h"

namespace Ui {
class ListsSubPage;
}

class ListsSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit ListsSubPage(QWidget *parent = nullptr);
	~ListsSubPage();

	void AppendList(ListItem* list);
	void InsertList(ListItem* list, int idx);
	void RemoveList(ListItem* list);

	void UpdateListNumbers(int idx);
	void UpdateColors();


	ListItem* SafeGetList(int idx);

	void Update(const std::vector<List>& lists);
	void Clear();

	void set_list_size(int size);
	int get_list_size();
	void changeEvent(QEvent* event);
signals:
	void GoToCreateList();
	void GoToProducts(const List& list);

private slots:
	void OnListClicked(ListItem* list);

private:
	Ui::ListsSubPage *m_ui;
	int m_list_size;
};
