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

	void set_product(const PeriodicProduct& product);
	PeriodicProduct get_product();
signals:
	void EditProduct();
	void DeleteProduct();

private:
	Ui::PeriodicProductViewSubPage *m_ui;
	PeriodicProduct m_product;
};
