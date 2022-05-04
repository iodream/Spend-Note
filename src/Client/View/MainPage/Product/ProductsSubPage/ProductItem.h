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
	~ProductItem();

	void Update();

	Product get_product() const { return m_product; }

	void set_number(int number);
	int get_number();

	QString get_color();

private:
	void UpdateColor();

	Product m_product;

	int m_number{1};
	QString m_color;

	Ui::ProductItem *m_ui;
};
