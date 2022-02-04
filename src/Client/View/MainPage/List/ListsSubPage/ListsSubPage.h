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

	ListItem* SafeGetList(int idx);

	void Update(const std::vector<List>& lists);
	void Clear();

	void set_list_size(int size);
	int get_list_size();

signals:
	void AddItem();

private slots:
	void OnListClicked(ListItem* list);

private:
	Ui::ListsSubPage *m_ui;
	int m_list_size;
};
