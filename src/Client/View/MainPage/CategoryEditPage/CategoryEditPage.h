#pragma once

#include <QWidget>
#include "Entities/Entities.h"
namespace Ui {
class CategoryEditPage;
}

class CategoryEditPage : public QWidget
{
	Q_OBJECT

public:
	explicit CategoryEditPage(QWidget *parent = nullptr);
	~CategoryEditPage();
	void Update(const std::vector<ProductCategory>& categories);
	void Update(const std::vector<IncomeCategory>& categories);

	void UpdateColors();
signals:
	void AddIncomeCategory(IncomeCategory);
	void AddProductCategory(ProductCategory);
	void UpdateIncomeCategory(IncomeCategory&);
	void UpdateProductCategory(ProductCategory&);
	void RemoveIncomeCategory(IncomeCategoryId);
	void RemoveProductCategory(ProductCategoryId);

	void ClientError(const std::string& desc);

public slots:
	void OnEditCategoryClicked();
	void OnAddCategoryClicked();
	void OnRemoveClicked();
	void OnCategoryEditConfirmClicked();
	void OnCategoryAddConfirmClicked();
private:
	Ui::CategoryEditPage *ui;
};
