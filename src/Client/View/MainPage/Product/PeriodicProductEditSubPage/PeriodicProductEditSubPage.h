#pragma once

#include <QString>
#include <QWidget>
#include <QDateTime>

#include "Common.h"
#include "Entities/Entities.h"
#include "Utils.h"

namespace Ui {
class PeriodicProductEditSubPage;
}

class PeriodicProductEditSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit PeriodicProductEditSubPage(QWidget *parent = nullptr);
	~PeriodicProductEditSubPage();

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
	Ui::PeriodicProductEditSubPage *m_ui;
};
