#pragma once

#include <QWidget>
#include <QPushButton>
#include <QString>

#include "Client/Common.h"
#include "Client/Entities/Entities.h"

namespace Ui {
class ListItem;
}

class ListItem : public QPushButton
{
	Q_OBJECT

public:
	explicit ListItem(List list, QWidget *parent = nullptr);
	~ListItem();

	void Update();

	List get_list() const { return m_list; };

	void set_number(int number);
	int get_number() const;

	QString get_color();

private:
	void UpdateColor();

	List m_list;

	int m_number{1};
	QString m_color;

	Ui::ListItem *m_ui;
};
