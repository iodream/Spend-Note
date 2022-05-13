#pragma once

#include <QString>
#include <QWidget>
#include <QDateTime>

#include "Common.h"
#include "Entities/Entities.h"
#include "Utils.h"
#include "View/Constants.h"

namespace Ui {
class ProductEditSubPage;
}

class ProductEditSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit ProductEditSubPage(QWidget *parent = nullptr);
	~ProductEditSubPage();

	void set_product(const Product& product);
	Product get_product();

	void Update();
	void FillCategoryBox(const std::vector<ProductCategory>& categories);
	void SetRangeOfSpinBox();
	void SetMinimumDate(const QDate& date);
	void changeEvent(QEvent* event);

signals:
	void UpdateProduct();
	void AddProductCategory(ProductCategory);
	void UpdateCategories();


public slots:
	void OnNewCategoryPushed();
	void OnNewCategorySaved();
private:
	Ui::ProductEditSubPage *m_ui;
	Product m_product;
};
