#pragma once

#include <QWidget>

namespace Ui {
class CategoryEditPage;
}

class CategoryEditPage : public QWidget
{
	Q_OBJECT

public:
	explicit CategoryEditPage(QWidget *parent = nullptr);
	~CategoryEditPage();

private:
	Ui::CategoryEditPage *ui;
};

