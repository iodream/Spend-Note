#pragma once

#include <QPushButton>
#include <QString>

namespace Ui {
class Item;
}

class Item : public QPushButton
{
	Q_OBJECT

public:
	explicit Item(QString name, QWidget *parent = nullptr);
	~Item();

	void Update();
	void SetNumber(int number);
	int  GetNumber() const;
	int m_number{1};

private:
	QString m_name;
	Ui::Item *m_ui;
};
