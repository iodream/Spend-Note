#pragma once

#include <QString>
#include <QWidget>

#include "Common.h"

namespace Ui {
class ProductViewSubPage;
}

class ProductViewSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit ProductViewSubPage(QWidget *parent = nullptr);
	~ProductViewSubPage();
signals:
	void GoBack();
	void EditProduct();
	void DeleteProduct();

private:
	Ui::ProductViewSubPage *m_ui;
};
