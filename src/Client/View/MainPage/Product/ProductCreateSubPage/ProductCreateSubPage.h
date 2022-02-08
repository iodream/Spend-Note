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
	explicit ProductPage(QWidget *parent = nullptr);
	~ProductPage();
signals:
	void GoBack();
	void CreateList();

private:
	Ui::ProductCreateSubPage *m_ui;
};
