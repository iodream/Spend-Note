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

public slots:
	void OnEditCategoryClicked();
	void OnAddCategoryClicked();
	void OnRemoveClicked();
	void OnCategoryEditConfirmClicked();
	void OnCategoryAddConfirmClicked();
private:
	Ui::CategoryEditPage *ui;
};

