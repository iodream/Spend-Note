#pragma once

#include <QWidget>
#include <QPushButton>
#include <QString>

namespace Ui {
class ListItem;
}

class ListItem : public QPushButton
{
	Q_OBJECT

public:
	using IdType = int;

	explicit ListItem(IdType id, QWidget *parent = nullptr);
	~ListItem();

	void Update();

	void set_name(const QString& name);
	void set_buy_until(const QString& buy_until);
	void set_price(const QString& price);
	void set_is_purchased(bool is_purchased);

	QString get_name() { return m_name; };
	QString get_buy_until() { return m_buy_until; };
	QString get_price() { return m_price; };
	bool get_is_purchased() { return m_is_purchased; };
	IdType get_id() { return m_id; };

	void set_number(int number);
	int get_number();

	QString get_color();

private:
	void UpdateColor();

	IdType m_id;
	QString m_name;
	QString m_buy_until;
	QString m_price;
	bool m_is_purchased;

	int m_number{1};
	QString m_color;

	Ui::ListItem *m_ui;
};
