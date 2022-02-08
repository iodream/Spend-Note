#include "ListsSubPage.h"
#include "ui_ListsSubPage.h"
#include "Exception.h"

ListsSubPage::ListsSubPage(QWidget *parent)
	: QWidget(parent)
	, m_ui(new Ui::ListsSubPage)
{
	m_ui->setupUi(this);
	set_list_size(0);

	connect(
		m_ui->AddItemButton,
		&QPushButton::released,
		this,
		&ListsSubPage::GoToCreateList);
}

void ListsSubPage::AppendList(ListItem* list)
{
	InsertList(list, get_list_size());
}

void ListsSubPage::InsertList(ListItem* list, int idx)
{
	if (get_list_size() < idx || idx < 0) {
		throw Exception("Trying to insert a widget out of range");
	}
	m_ui->ItemsLayout->insertWidget(idx, list);
	connect(list, &ListItem::released, [this, list](){ emit OnListClicked(list); });
	list->set_number(idx + 1);
	set_list_size(get_list_size() + 1);
	UpdateListNumbers(idx + 1);
}

void ListsSubPage::UpdateListNumbers(int idx)
{
	while (idx < get_list_size())
	{
		auto* list = SafeGetList(idx);
		list->set_number(++idx);
		list->Update();
	}
}

void ListsSubPage::OnListClicked(ListItem* list)
{
	// should emit some signal to be handled on controller
}

ListItem* ListsSubPage::SafeGetList(int idx)
{
	QLayoutItem *layout = m_ui->ItemsLayout->itemAt(idx);
	if (!layout) {
		throw Exception("Failed to get list layout");
	}
	auto* list = qobject_cast<ListItem*>(layout->widget());
	if (!list) {
		throw Exception("Failed to get list widget pointer");
	}
	return list;
}

void ListsSubPage::RemoveList(ListItem* list)
{
	int idx = list->get_number() - 1;
	QLayoutItem *layout = m_ui->ItemsLayout->takeAt(idx);
	if (!layout) {
		throw Exception("Failed to get list layout");
	}

	delete layout->widget();
	delete layout;
	set_list_size(get_list_size() - 1);

	UpdateListNumbers(idx);
}

void ListsSubPage::set_list_size(int size)
{
	m_list_size = size;
	m_ui->ListSize->setText(QString("%1").arg(m_list_size));
	m_ui->ListSize->show();
}

int ListsSubPage::get_list_size()
{
	return m_list_size;
}

ListsSubPage::~ListsSubPage()
{
	delete m_ui;
}

void ListsSubPage::Update(const std::vector<List>& lists)
{
	Clear();
	for (auto it = lists.begin(); it != lists.end(); it++) {
		ListItem* item = new ListItem(it->id);
		item->set_name(it->name);
		// currently ignoring other fields
		item->Update();
		AppendList(item);
	}
}

void ListsSubPage::Clear()
{
	while (get_list_size()) {
		QLayoutItem *layout = m_ui->ItemsLayout->takeAt(0);
		if (!layout) {
			throw Exception("Failed to get product layout");
		}

		delete layout->widget();
		delete layout;
		set_list_size(get_list_size() - 1);
	}
}
