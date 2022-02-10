#include <QPushButton>

#include "ListEditSubPage.h"
#include "ui_ListEditSubPage.h"
#include "Exception.h"

ListEditSubPage::ListEditSubPage(QWidget *parent)
	: QWidget(parent)
	, m_ui(new Ui::ListEditSubPage)
{
	m_ui->setupUi(this);

	connect(
		m_ui->SaveButton,
		&QPushButton::clicked,
		[this](){ m_list.name = m_ui->ListName->text(); emit UpdateList(m_list); });


	connect(
		m_ui->GoBackButton,
		&QPushButton::released,
		[this](){ emit GoBack(3);});
}

ListEditSubPage::~ListEditSubPage()
{
	delete m_ui;
}

void ListEditSubPage::set_list(const List& list)
{
	m_list = list;
}

List ListEditSubPage::get_list() const
{
	return m_list;
}

void ListEditSubPage::Update(const List& list)
{
	set_list(list);
	m_ui->ListName->setText(m_list.name);
}
