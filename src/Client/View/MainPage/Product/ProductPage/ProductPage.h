#pragma once

#include <QWidget>

#include "../ListItem/ListItem.h"

namespace Ui {
class ProductPage;
}

class ProductPage : public QWidget
{
	Q_OBJECT

public:
	using IdType = int;

	explicit ProductPage(QWidget *parent = nullptr);
	~ProductPage();

	void Setup(ListItem* list_item);

private:
	Ui::ProductPage *m_ui;

	ListItem* m_list_item;

signals:
	void GoBack();

private slots:
	void OnGoBackClicked();
};
