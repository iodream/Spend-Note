#pragma once

#include <QString>
#include <QWidget>

#include "Common.h"
#include "Entities/Entities.h"

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
signals:
	void UpdateProduct();

private:
	Ui::ProductEditSubPage *m_ui;
	Product m_product;
};
