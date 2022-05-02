#include <QPushButton>

#include "ListCreateSubPage.h"
#include "ui_ListCreateSubPage.h"
#include "Exception.h"

ListCreateSubPage::ListCreateSubPage(QWidget *parent)
	: QWidget(parent)
	, m_ui(new Ui::ListCreateSubPage)
	, m_list_size(0)
{
	m_ui->setupUi(this);

	connect(
		m_ui->SaveButton,
		&QPushButton::released,
		this,
		&ListCreateSubPage::CreateList);
	connect(
		m_ui->AddItemButton,
		&QPushButton::released,
		this,
		&ListCreateSubPage::GoToQuickCreateProduct);
	connect(
		m_ui->ClearAllButton,
		&QPushButton::released,
		this,
		&ListCreateSubPage::OnClearAll);
}

void ListCreateSubPage::changeEvent(QEvent* event)
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

ListCreateSubPage::~ListCreateSubPage()
{
	delete m_ui;
}

QString ListCreateSubPage::GetListName()
{
	return m_ui->lineEdit->text();
}

void ListCreateSubPage::ClearItems()
{
	m_ui->lineEdit->setText("");

	while (GetListSize()) {
		QLayoutItem *layout = m_ui->ItemsLayout->takeAt(0);
		if (!layout) {
			throw Exception("Failed to get product layout");
		}

		delete layout->widget();
		delete layout;
		SetListSize(GetListSize() - 1);

	}
	items.clear();
}

void ListCreateSubPage::RemoveItem(Item* item)
{
	int idx = item->GetNumber() - 1;
	QLayoutItem *layout = m_ui->ItemsLayout->takeAt(idx);
	if (!layout) {
		throw Exception("Failed to get list layout");
	}

	delete layout->widget();
	delete layout;
	SetListSize(GetListSize() - 1);
}

void ListCreateSubPage::SetListSize(int size)
{
	m_list_size = size;
}

int ListCreateSubPage::GetListSize()
{
	return m_list_size;
}

void ListCreateSubPage::AddProductToVector(Product product)
{
	items.push_back(product);
}

std::vector<Product>& ListCreateSubPage::GetItems()
{
	return items;
}

void ListCreateSubPage::OnClearAll()
{
	ClearItems();
}

void ListCreateSubPage::AppendItem(Item* item)
{
	InsertItem(item, GetListSize());
}
IdType ListCreateSubPage::GetListState()
{
	return qvariant_cast<IdType>(m_ui->ListState->currentData());
}

void ListCreateSubPage::Update()
{
	m_ui->lineEdit->setText("");
}

void ListCreateSubPage::InsertItem(Item* item, int idx)
{
	m_ui->ItemsLayout->insertWidget(idx, item);
	item->SetNumber(idx + 1);
	SetListSize(GetListSize() + 1);
}
void ListCreateSubPage::FillStateBox(const std::vector<ListState> &states)
{
	m_ui->ListState->clear();
	for(const auto& el : states)
	{
		m_ui->ListState->addItem(el.name, el.id);
	}
}
