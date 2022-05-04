#pragma once

#include <QString>
#include <QWidget>
#include <QDateTime>

#include "Common.h"
#include "Entities/Entities.h"
#include "View/Constants.h"

namespace Ui {
class PeriodicProductViewSubPage;
}

class PeriodicProductViewSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit PeriodicProductViewSubPage(QWidget *parent = nullptr);
	~PeriodicProductViewSubPage();

	void Update();

	void set_product(const Product& product);
	Product get_product();
signals:
	void EditProduct();
	void DeleteProduct();

private:
	Ui::PeriodicProductViewSubPage *m_ui;
	Product m_product;
};
