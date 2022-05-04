#pragma once

#include <QString>
#include <QWidget>
#include <QDateTime>

#include "Common.h"
#include "Entities/Entities.h"
#include "Utils.h"

namespace Ui {
class PeriodicProductViewSubPage;
}

class PeriodicProductViewSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit PeriodicProductViewSubPage(QWidget *parent = nullptr);
	~PeriodicProductViewSubPage();

	QString GetName();
	Money GetPrice();
	BigInt GetAmount();
	bool GetIsBought();
	QString GetGenerateUntil();
	BigInt GetPriority();
	IdType GetCategoryId();
	QString GetCategoryName();

	void Clear();
	void FillCategoryBox(const std::vector<ProductCategory>& categories);
	void SetRangeOfSpinBox();
	void SetMinimumDate(const QDate& date);

signals:
	void CreateProduct();
	void AddProductCategory(ProductCategory);
	void UpdateCategories();

public slots:
	void OnNewCategoryPushed();
	void OnNewCategorySaved();

private:
	Ui::PeriodicProductViewSubPage *m_ui;
};
