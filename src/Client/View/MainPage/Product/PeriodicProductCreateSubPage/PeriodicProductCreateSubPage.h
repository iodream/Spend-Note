#pragma once

#include <QString>
#include <QWidget>
#include <QDateTime>

#include "Common.h"
#include "Entities/Entities.h"
#include "Utils.h"

namespace Ui {
class PeriodicProductCreateSubPage;
}

class PeriodicProductCreateSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit PeriodicProductCreateSubPage(QWidget *parent = nullptr);
	~PeriodicProductCreateSubPage();

	QString GetName();
	Money GetPrice();
	BigInt GetAmount();
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
	Ui::PeriodicProductCreateSubPage *m_ui;
};
