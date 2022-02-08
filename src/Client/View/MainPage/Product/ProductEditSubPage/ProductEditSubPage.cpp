#include "ProductEditSubPage.h"
#include "ui_ProductEditSubPage.h"

ProductEditSubPage::ProductEditSubPage(QWidget *parent) :
	QWidget(parent),
	m_ui(new Ui::ProductEditSubPage)
{
	m_ui->setupUi(this);

	connect(
		m_ui->SaveButton,
		&QPushButton::clicked,
		this,
		&ProductEditSubPage::UpdateProduct);

	connect(
		m_ui->GoBackButton,
		&QPushButton::clicked,
		this,
		&ProductEditSubPage::GoBack);

	connect(
		m_ui->DeleteButton,
		&QPushButton::clicked,
		this,
		&ProductEditSubPage::DeleteProduct);
}

ProductEditSubPage::~ProductEditSubPage()
{
	delete m_ui;
}
