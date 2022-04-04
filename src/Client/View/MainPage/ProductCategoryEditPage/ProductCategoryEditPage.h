#pragma once

#include <QWidget>

namespace Ui {
class ProductCategoryEditPage;
}

class ProductCategoryEditPage : public QWidget
{
	Q_OBJECT

public:
	explicit ProductCategoryEditPage(QWidget *parent = nullptr);
	~ProductCategoryEditPage();

private:
	Ui::ProductCategoryEditPage *ui;
};

