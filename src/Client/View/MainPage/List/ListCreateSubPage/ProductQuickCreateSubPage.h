#pragma once

#include <QString>
#include <QWidget>

#include "Common.h"
#include "Utils.h"
#include "Entities/Entities.h"

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
	IdType GetCategoryId();
	QString GetCategoryName();
	void SetRangeOfSpinBox();
	void SetMinimumDate(const QDate& date);

	void Clear();
	void FillCategoryBox(const std::vector<ProductCategory>& categories);

signals:
	void QuickAddItem();
	void AddProductCategory(ProductCategory);
	void UpdateCategories();

public slots:
	void OnNewCategoryPushed();
	void OnNewCategorySaved();

private:
	Ui::ProductQuickCreateSubPage *m_ui;
};
