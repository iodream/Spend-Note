#pragma once

#include "../../Product/ProductsSubPage/ProductItem.h"

namespace Ui {
class DailyListSubPage;
}

class DailyListSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit DailyListSubPage(QWidget *parent = nullptr);
	~DailyListSubPage();

	void AppendProduct(ProductItem* product);
	void InsertProduct(ProductItem* product, int idx);

	void UpdateNumbers(int idx);

	ProductItem* SafeGetProduct(int idx);

	void Update(const std::vector<Product>& products);
	void Clear();

	void set_list_size(int size);
	int get_list_size();

	void UpdateColors();
private:
	Ui::DailyListSubPage *m_ui;

	int m_list_size;

signals:
	void GoToProductView(const Product& product);
	void ProductClicked(const Product& product);

private slots:
	void OnProductClicked(ProductItem* product);

};

