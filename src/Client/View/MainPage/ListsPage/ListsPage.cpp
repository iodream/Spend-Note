#include "ListsPage.h"
#include "ui_ListsPage.h"
#include "Exception.h"

ListsPage::ListsPage(QWidget *parent)
	: QWidget(parent)
	, m_ui(new Ui::ListsPage)
{
	m_ui->setupUi(this);
	ListsItem* it = new ListsItem(1, "list1", ITEM_COLOR_YES, this);
	m_ui->ItemsLayout->insertWidget(0,it);


	connect(it, SIGNAL(released()), this, SLOT(onSwitchPage()));
}

void ListsPage::onSwitchPage()
{
	emit SwitchPage();
}
//void ListsPage::UpdateData(ListOutDTO dto)
//{
//	int i=0;
//	std::vector<ListsItem*> vec;
//	foreach (const QJsonValue& value, dto.data) {
//			i++;
//			QJsonObject obj = value.toObject();
//			QString listname = obj["name"].toString();
//			QString liststate = obj["state"].toString();
//			ListsItem* it = new ListsItem(i, listname, ITEM_COLOR_YES, this);
//			vec.push_back(it);
//	}
//	for(int i=0;i<vec.size();++i)
//		m_ui->ItemsLayout->insertWidget(i,vec[i]);
//}


ListsPage::~ListsPage()
{
	delete m_ui;
}

