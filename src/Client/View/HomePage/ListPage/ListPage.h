#pragma once

#include <QString>
#include <QWidget>

#include "ListItem.h"

namespace Ui {
class ListPage;
}

class ListPage : public QWidget
{
	Q_OBJECT

public:
	using IdType = int;

	explicit ListPage(QString name, IdType id, QWidget *parent=nullptr);
	~ListPage();

	void AppendProduct(ListItem* product);
	void InsertProduct(ListItem* product, int idx);
	void RemoveProduct(ListItem* product);

	void UpdateProductNumbers(int idx);

	ListItem* SafeGetProduct(int idx);
private:
	void set_list_size(int size);
	int get_list_size();

	Ui::ListPage *ui;

	QString m_name;
	IdType m_id;

	int m_list_size;

private slots:
	// temporary plugs, should be reimplemented
	void OnAddProduct();
	void OnProductClicked();
};
