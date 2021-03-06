#include <QPushButton>

#include "ListViewSubPage.h"
#include "ui_ListViewSubPage.h"
#include "Exception.h"
#include "Net/Parsing.h"
#include "Models/List/GetListsModel.h"

ListViewSubPage::ListViewSubPage(QWidget *parent)
	: QWidget(parent)
	, m_ui(new Ui::ListViewSubPage)
{
	m_ui->setupUi(this);

	connect(
		m_ui->EditButton,
		&QPushButton::released,
		[this](){ emit GoToEditList(m_list); });
	connect(
		m_ui->DeleteButton,
		&QPushButton::clicked,
		[this](){ emit DeleteList(m_list); });
}

void ListViewSubPage::changeEvent(QEvent* event)
{
	if(event)
	{
		switch(event->type())
		{
		case QEvent::LanguageChange:
			m_ui->retranslateUi(this);
			break;
		}

		QWidget::changeEvent(event);
	}
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

void ListViewSubPage::Update(const List& list)
{
	set_list(list);
	m_ui->ListName->setText(m_list.name);
	m_ui->StateName->setText(m_list.state.name);
}
