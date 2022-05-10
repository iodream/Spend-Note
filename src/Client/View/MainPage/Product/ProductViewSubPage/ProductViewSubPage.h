#pragma once

#include <QString>
#include <QWidget>
#include <QDateTime>

#include "Common.h"
#include "Entities/Entities.h"
#include "View/Constants.h"

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
	void changeEvent(QEvent* event);
signals:
	void EditProduct();
	void DeleteProduct();

private:
	Ui::ProductViewSubPage *m_ui;
	Product m_product;
};
