#pragma once

#include <QString>
#include <QWidget>

#include "ProductItem.h"
#include "Client/Entities/Entities.h"

namespace Ui {
class ProductsSubPage;
}

class ProductsSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit ProductsSubPage(QWidget *parent=nullptr);
	~ProductsSubPage();

	void AppendProduct(ProductItem* product);
	void InsertProduct(ProductItem* product, int idx);
	void RemoveProduct(ProductItem* product);

	void UpdateProductNumbers(int idx);

	ProductItem* SafeGetProduct(int idx);

	void Update(const std::vector<Product>& products);
	void UpdateColors();

	void Clear();

	void changeEvent(QEvent* event);

	void set_regular_list_size(int size);
	int get_regular_list_size();

	void set_regular_list(List list);
	List get_regular_list();


signals:
	void GoToCreateProduct(IdType list_id);
	void GoToViewList();
	void ProductClicked(const Product& product);

private slots:
	void OnProductClicked(ProductItem* product);

private:
	Ui::ProductsSubPage *m_ui;
	List m_regular_list, m_periodic_list;
	int m_regular_list_size, m_periodic_list_size;
};
