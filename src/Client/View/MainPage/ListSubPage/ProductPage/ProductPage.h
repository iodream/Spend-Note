#pragma once

#include <QWidget>

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

	void Setup(QString name, IdType id, QString buy_until, QString price, bool is_purchased);

private:
	Ui::ProductPage *m_ui;

private slots:
	void OnGoBackClicked();
};
