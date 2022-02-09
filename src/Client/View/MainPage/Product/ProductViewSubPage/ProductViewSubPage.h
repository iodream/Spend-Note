#pragma once

#include <QString>
#include <QWidget>

#include "Common.h"
#include "Entities/Entities.h"

namespace Ui {
class ProductViewSubPage;
}

class ProductViewSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit ProductViewSubPage(QWidget *parent = nullptr);
	~ProductViewSubPage();

	void Update();

	void set_product(const Product& product);
	Product get_product();
signals:
	void GoBack(int n=1);
	void EditProduct();
	void DeleteProduct();

private:
	Ui::ProductViewSubPage *m_ui;
	Product m_product;
};
