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
}

ListCreateSubPage::~ListCreateSubPage()
{
	delete m_ui;
}

QString ListCreateSubPage::GetListName()
{
	return m_ui->lineEdit->text();
}

IdType ListCreateSubPage::GetListState()
{
	return qvariant_cast<IdType>(m_ui->ListState->currentData());
}

void ListCreateSubPage::Update()
{
	m_ui->lineEdit->setText("");
}

void ListCreateSubPage::FillStateBox(const std::vector<ListState> &states)
{
	for(const auto& el : states)
	{
		m_ui->ListState->addItem(el.name, el.id);
	}
}
