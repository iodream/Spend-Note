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
	void FillStateBox(const std::vector<ListState>& states);

	void set_list(const List& list);
	List get_list();
	IdType get_state_id() const;
	void changeEvent(QEvent* event);
signals:
	void UpdateListView(PageData& data);

	void UpdateList();

private:
	Ui::ListEditSubPage *m_ui;
	List m_list;
};
