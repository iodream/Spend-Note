#pragma once

#include <QString>
#include <QWidget>

#include "Common.h"

namespace Ui {
class ProductEditSubPage;
}

class ProductEditSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit ProductEditSubPage(QWidget *parent = nullptr);
	~ProductEditSubPage();
signals:
	void GoBack();
	void UpdateProduct();

private:
	Ui::ProductEditSubPage *m_ui;
};
