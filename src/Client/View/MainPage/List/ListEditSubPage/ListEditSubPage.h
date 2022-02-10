#pragma once

#include <QString>
#include <QWidget>

#include "Entities/Entities.h"
#include "Entities/PageData.h"

namespace Ui {
class ListEditSubPage;
}

class ListEditSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit ListEditSubPage(QWidget *parent=nullptr);
	~ListEditSubPage();

	void Update(const List& list);

	void set_list(const List& list);
	List get_list() const;

signals:
	void GoBack(int n=1);
	void UpdateListView(PageData& data);

	void UpdateList(List);

private:
	Ui::ListEditSubPage *m_ui;
	List m_list;
};
