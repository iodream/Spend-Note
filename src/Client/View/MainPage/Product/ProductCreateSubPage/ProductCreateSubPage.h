#pragma once

#include <QString>
#include <QWidget>
#include <QDateTime>

#include "Common.h"
#include "Entities/Entities.h"
#include "Utils.h"

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
	IdType GetCategoryId();
	QString GetCategoryName();

	void Clear();
	void FillCategoryBox(const std::vector<ProductCategory>& categories);
	void SetRangeOfSpinBox();

signals:
	void CreateProduct();

private:
	Ui::ProductCreateSubPage *m_ui;
};
