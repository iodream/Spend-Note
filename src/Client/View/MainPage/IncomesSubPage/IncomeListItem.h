#pragma once

#include <QWidget>
#include <QPushButton>
#include <QString>

namespace Ui {
class IncomeListItem;
}

class IncomeListItem : public QPushButton
{
	Q_OBJECT

public:
	using IdType = int;

	explicit IncomeListItem(IdType id, QWidget *parent = nullptr);
	~IncomeListItem();

	void Update();

	void set_name(const QString& name);
	void set_amount(int amount);
	void set_expiration_time(const QString& expiration_time);
	void set_category(const QString& category);

	void set_number(int number);
	int get_number();

	QString get_color();

private:
	void UpdateColor();

	IdType m_id;
	QString m_name;
	int m_amount;
	QString m_expiration_time;
	QString m_category;

	int m_number{1};
	QString m_color;

	Ui::IncomeListItem *m_ui;
};
