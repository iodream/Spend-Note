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
		[this](){m_list.name = m_ui->ListName->text(); emit UpdateList(m_list); });
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

IdType ListEditSubPage::get_state_id() const
{
	return m_list.state.id;
}

void ListEditSubPage::Update(const List& list)
{
	set_list(list);
	m_ui->ListName->setText(m_list.name);
	m_ui->ListState->setPlaceholderText(m_list.state.name);
}

void ListEditSubPage::FillStateBox(const std::vector<ListState> &states)
{
	for(const auto& el : states)
	{
		m_ui->ListState->addItem(el.name, el.id);
	}
}
