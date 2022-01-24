#pragma once

#include <QString>
#include <QWidget>

#include "ProductItem.h"

namespace Ui {
class ProductsSubPage;
}

class ProductsSubPage : public QWidget
{
	Q_OBJECT

public:
	using IdType = int;

	explicit ProductsSubPage(QWidget *parent=nullptr);
	~ProductsSubPage();

	void AppendProduct(ProductItem* product);
	void InsertProduct(ProductItem* product, int idx);
	void RemoveProduct(ProductItem* product);

	void UpdateProductNumbers(int idx);

	ProductItem* SafeGetProduct(int idx);
private:
	void OnProductClicked(ProductItem* product);

	void set_list_size(int size);
	int get_list_size();

	Ui::ProductsSubPage *m_ui;

	QString m_name;
	IdType m_id;

	int m_list_size;
};
