#pragma once

#include <QString>
#include <QWidget>
#include <QDateTime>

#include "Entities/Entities.h"
#include "Utils.h"
#include "View/Constants.h"


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

	void set_product(const PeriodicProduct& product);
	PeriodicProduct get_product();

	void Clear();
	void FillCategoryBox(const std::vector<ProductCategory>& categories);
	void SetRangeOfSpinBox();
	void Update();
	void SetMinimumDate(const QDate& date);

signals:
	void UpdateProduct();
	void AddProductCategory(ProductCategory);
	void UpdateCategories();

public slots:
	void OnNewCategoryPushed();
	void OnNewCategorySaved();

private:
	Ui::PeriodicProductEditSubPage *m_ui;
	PeriodicProduct m_periodic_product;
};
