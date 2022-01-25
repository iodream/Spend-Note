#pragma once

#include <QWidget>
#include <QPushButton>
#include <QString>

#include "Client/Common.h"


namespace Ui {
class ListItem;
}

class ListItem : public QPushButton
{
	Q_OBJECT

public:
	explicit ListItem(IdType id, QWidget *parent = nullptr);
	~ListItem();

	void Update();

	void set_name(const QString& name);

	QString get_name() const { return m_name; };
	IdType get_id() const { return m_id; };

	void set_number(int number);
	int get_number() const;

	QString get_color();

private:
	void UpdateColor();

	IdType m_id;
	QString m_name;

	int m_number{1};
	QString m_color;

	Ui::ListItem *m_ui;
};
