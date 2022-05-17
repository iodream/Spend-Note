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

	void AppendPeriodicProduct(ProductItem* product);
	void InsertPeriodicProduct(ProductItem* product, int idx);
	void RemovePeriodicProduct(ProductItem* product);

	void UpdateProductNumbers(int idx);
	void UpdatePeriodicProductNumbers(int idx);

	ProductItem* SafeGetProduct(int idx);
	ProductItem* SafeGetPeriodicProduct(int idx);

	void Update(const std::vector<Product>& products);
	void Update(const std::vector<PeriodicProduct>& products);
	void UpdateColors();

	void Clear();
	void ClearPeriodic();

	void changeEvent(QEvent* event);

	void set_regular_list_size(int size);
	int get_regular_list_size();

	void set_regular_list(List list);
	List get_regular_list();

	void set_periodic_list_size(int size);
	int get_periodic_list_size();

	void set_periodic_list(List list);
	List get_periodic_list();

signals:
	void GoToCreateProduct(IdType list_id);
	void GoToCreatePeriodicProduct(IdType list_id);
	void GoToViewList();
	void ProductClicked(const Product& product);
	void PeriodicProductClicked(const PeriodicProduct& product);

private slots:
	void OnProductClicked(ProductItem* product);
	void OnPeriodicProductClicked(ProductItem* product);

private:
	Ui::ProductsSubPage *m_ui;
	List m_regular_list, m_periodic_list;
	int m_regular_list_size, m_periodic_list_size;
};
