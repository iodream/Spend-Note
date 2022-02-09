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

	void Update();

	void set_list(const List& list);
	List get_list() const;

signals:
	void GoBack();
	void EditList(List);
	void DeleteList(List);

private:
	Ui::ListViewSubPage *m_ui;
	List m_list;
};
