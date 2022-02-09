#pragma once

#include <QString>
#include <QWidget>

#include "Common.h"

namespace Ui {
class ProductCreateSubPage;
}

class ProductCreateSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit ProductCreateSubPage(QWidget *parent = nullptr);
	~ProductCreateSubPage();

	QString GetName();
	Money GetPrice();
	BigInt GetAmount();
	bool GetIsBought();
	QString GetBuyUntil();
	BigInt GetPriority();

	void Clear();
signals:
	void GoBack();
	void CreateProduct();

private:
	Ui::ProductCreateSubPage *m_ui;
};
