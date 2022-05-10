#pragma once

#include <QString>
#include <QWidget>

#include "Entities/Entities.h"

namespace Ui {
class ListViewSubPage;
}

class ListViewSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit ListViewSubPage(QWidget *parent=nullptr);
	~ListViewSubPage();

	void Update(const List& list);

	void set_list(const List& list);
	List get_list() const;
	void changeEvent(QEvent* event);

signals:
	void GoToEditList(List list);
	void DeleteList(List);

private:
	Ui::ListViewSubPage *m_ui;
	List m_list;
};
