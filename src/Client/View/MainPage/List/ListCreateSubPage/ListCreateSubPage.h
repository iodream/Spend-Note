#pragma once

#include <QString>
#include <QWidget>

#include "Common.h"
#include "View/Constants.h"

#include "Entities/Entities.h"
#include "Item.h"
namespace Ui {
class ListCreateSubPage;
}

class ListCreateSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit ListCreateSubPage(QWidget *parent=nullptr);
	~ListCreateSubPage();

	QString GetListName();

	void AppendItem(Item* item);
	void InsertItem(Item* item, int idx);
	void RemoveItem(Item* item);
	void ClearItems();

	void AddProductToVector(Product);
	std::vector<Product>& GetItems();

	void FillStateBox(const std::vector<ListState>& states);
	IdType GetListState();
	void Update();

private:
	void SetListSize(int size);
	int  GetListSize();

signals:
	void CreateList();
	void ChangeSubPage(MainSubPages page);
	void GoToQuickCreateProduct();

public slots:
	void OnClearAll();

private:
	Ui::ListCreateSubPage *m_ui;
	std::vector<Product> items;
	int m_list_size;
};
