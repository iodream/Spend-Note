#pragma once

#include <QString>
#include <QWidget>

#include "Entities/Entities.h"

namespace Ui {
class ListEditSubPage;
}

class ListEditSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit ListEditSubPage(QWidget *parent=nullptr);
	~ListEditSubPage();

	void Update();

	void set_list(const List& list);
	List get_list() const;

signals:
	void GoBack();
	void UpdateList(List);

private:
	Ui::ListEditSubPage *m_ui;
	List m_list;
};
