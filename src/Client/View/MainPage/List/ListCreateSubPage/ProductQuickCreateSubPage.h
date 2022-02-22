#pragma once

#include <QString>
#include <QWidget>

#include "Common.h"

namespace Ui {
class ProductQuickCreateSubPage;
}

class ProductQuickCreateSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit ProductQuickCreateSubPage(QWidget *parent = nullptr);
	~ProductQuickCreateSubPage();

	QString GetName();
	Money GetPrice();
	BigInt GetAmount();
	bool GetIsBought();
	QString GetBuyUntil();
	BigInt GetPriority();

	void Clear();
signals:
	void QuickAddItem();

private:
	Ui::ProductQuickCreateSubPage *m_ui;
};
