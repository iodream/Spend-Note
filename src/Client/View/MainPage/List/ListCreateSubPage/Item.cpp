#include "Item.h"
#include "ui_Item.h"

#include "View/MainPage/MainPage.h"

Item::Item(QString name, QWidget *parent)
	: QPushButton(parent)
	, m_ui(new Ui::Item)
	, m_name(name)
{
	m_ui->setupUi(this);
	Update();
	setStyleSheet("background-color:" + QString(MainPage::ColorSettings::LIST_ACTIVE));
}

Item::~Item()
{
	delete m_ui;
}

void Item::Update()
{
	m_ui->ListName->setText(m_name);
	m_ui->Holder->show();
}

void Item::SetNumber(int number)
{
	m_number = number;
	m_ui->Number->setText(QString("%1").arg(m_number));
	Update();
}

int Item::GetNumber() const
{
	return m_number;
}
