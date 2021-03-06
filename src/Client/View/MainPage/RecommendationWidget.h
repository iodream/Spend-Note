#pragma once

#include <QWidget>
#include "Product/ProductsSubPage/ProductItem.h"

namespace Ui {
class RecommendationWidget;
}

class RecommendationWidget : public QWidget
{
	Q_OBJECT

public:
	explicit RecommendationWidget(QWidget *parent = nullptr);
	~RecommendationWidget();

	void AppendProduct(ProductItem* Item);
	void InsertProduct(ProductItem* Item, int idx);
	void RemoveProduct();
	void changeEvent(QEvent* event);

	ProductItem* SafeGetProduct(int idx);
	int GetListSize();
	void Clear();
	void SetListSize(int size);

	bool bClosed;
private:
	Ui::RecommendationWidget *m_ui;
	int m_list_size;

signals:
	void RecommendationClosed();
	void GoToProductView(const Product& product);

public slots:
	void OnProductClicked(ProductItem* product);

};
