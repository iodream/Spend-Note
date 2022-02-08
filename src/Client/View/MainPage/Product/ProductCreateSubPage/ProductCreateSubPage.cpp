#include "ProductCreateSubPage.h"
#include "ui_ProductCreateSubPage.h"

ProductCreateSubPage::ProductCreateSubPage(QWidget *parent) :
	QWidget(parent),
	m_ui(new Ui::ProductCreateSubPage)
{
	m_ui->setupUi(this);

	connect(
		m_ui->SaveButton,
		&QPushButton::released,
		this,
		&ProductCreateSubPage::CreateList);

	connect(
		m_ui->GoBackButton,
		&QPushButton::released,
		this,
		&ProductCreateSubPage::GoBack);
}

ProductPage::~ProductPage()
{
	delete m_ui;
}
