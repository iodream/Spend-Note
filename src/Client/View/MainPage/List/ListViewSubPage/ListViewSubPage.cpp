#include <QPushButton>

#include "ListViewSubPage.h"
#include "ui_ListViewSubPage.h"
#include "Exception.h"

ListViewSubPage::ListViewSubPage(QWidget *parent)
	: QWidget(parent)
	, m_ui(new Ui::ListViewSubPage)
{
	m_ui->setupUi(this);

	connect(
		m_ui->EditButton,
		&QPushButton::released,
		[this](){ emit EditList(m_list); });

	connect(
		m_ui->GoBackButton,
		&QPushButton::released,
		this,
		&ListViewSubPage::GoBack);

	connect(
		m_ui->DeleteButton,
		&QPushButton::clicked,
		[this](){ emit DeleteList(m_list); });
}

ListViewSubPage::~ListViewSubPage()
{
	delete m_ui;
}

void ListViewSubPage::set_list(const List& list)
{
	m_list = list;
}

List ListViewSubPage::get_list() const
{
	return m_list;
}

void ListViewSubPage::Update()
{
	m_ui->ListName->setText(m_list.name);
}
