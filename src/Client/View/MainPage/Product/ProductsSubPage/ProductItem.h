#pragma once

#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QDateTime>

#include "Client/Common.h"
#include "Client/Entities/Entities.h"

namespace Ui {
class ProductItem;
}

class ProductItem : public QPushButton
{
	Q_OBJECT

public:
	using IdType = int;

	explicit ProductItem(Product product, QWidget *parent = nullptr);
	explicit ProductItem(PeriodicProduct product, QWidget *parent = nullptr);
	~ProductItem();

	void Update();

	Product get_product() const { return m_product; }
	QString get_color();
	void set_number(int number);
	int get_number();
	void HideCheck();
	void SetText(const QString&);

	void changeEvent(QEvent* event);

private:
	void UpdateColor();
	Product m_product;
	PeriodicProduct m_periodic_product;
	int m_number{1};
	QString m_color;

	Ui::ProductItem *m_ui;
};
