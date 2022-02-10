#include <QPushButton>

#include "ListCreateSubPage.h"
#include "ui_ListCreateSubPage.h"
#include "Exception.h"

ListCreateSubPage::ListCreateSubPage(QWidget *parent)
	: QWidget(parent)
	, m_ui(new Ui::ListCreateSubPage)
{
	m_ui->setupUi(this);

	connect(
		m_ui->SaveButton,
		&QPushButton::released,
		this,
		&ListCreateSubPage::CreateList);

	connect(
		m_ui->GoBackButton,
		&QPushButton::released,
		[this](){ emit GoBack();});
}

ListCreateSubPage::~ListCreateSubPage()
{
	delete m_ui;
}

QString ListCreateSubPage::GetListName()
{
	return m_ui->lineEdit->text();
}

void ListCreateSubPage::Update()
{
	m_ui->lineEdit->setText("");
}
