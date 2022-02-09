#include "ProductCreateSubPage.h"
#include "ui_ProductCreateSubPage.h"

ProductCreateSubPage::ProductCreateSubPage(QWidget *parent) :
	QWidget(parent),
	m_ui(new Ui::ProductCreateSubPage)
{
	m_ui->setupUi(this);

	connect(
		m_ui->SaveButton,
		&QPushButton::clicked,
		this,
		&ProductCreateSubPage::CreateProduct);

	connect(
		m_ui->GoBackButton,
		&QPushButton::clicked,
		this,
		&ProductCreateSubPage::GoBack);
}

ProductCreateSubPage::~ProductCreateSubPage()
{
	delete m_ui;
}
