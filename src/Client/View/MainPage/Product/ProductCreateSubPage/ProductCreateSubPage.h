#pragma once

#include <QString>
#include <QWidget>

#include "Common.h"

namespace Ui {
class ProductCreateSubPage;
}

class ProductCreateSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit ProductCreateSubPage(QWidget *parent = nullptr);
	~ProductCreateSubPage();
signals:
	void GoBack(int n=1);
	void CreateProduct();

private:
	Ui::ProductCreateSubPage *m_ui;
};
