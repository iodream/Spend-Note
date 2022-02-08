#include "ProductViewSubPage.h"
#include "ui_ProductEditSubPage.h"

ProductViewSubPage::ProductViewSubPage(QWidget *parent) :
	QWidget(parent),
	m_ui(new Ui::ProductViewSubPage)
{
	m_ui->setupUi(this);

	connect(
		m_ui->EditButton,
		&QPushButton::clicked,
		this,
		&ProductViewSubPage::EditProduct);

	connect(
		m_ui->GoBackButton,
		&QPushButton::clicked,
		this,
		&ProductViewSubPage::GoBack);

	connect(
		m_ui->DeleteButton,
		&QPushButton::clicked,
		this,
		&ProductViewSubPage::DeleteProduct);
}

ProductViewSubPage::~ProductViewSubPage()
{
	delete m_ui;
}
