#pragma once

#include <QString>
#include <QWidget>

#include "ListItem/ListItem.h"
#include "ProductPage/ProductPage.h"
#include "../../Constants.h"

namespace Ui {
class ListSubPage;
}

class ListSubPage : public QWidget
{
	Q_OBJECT

public:
	using IdType = int;

	explicit ListSubPage(const QString& name, IdType id, QWidget *parent=nullptr);
	~ListSubPage();

	void AppendProduct(ListItem* product);
	void InsertProduct(ListItem* product, int idx);
	void RemoveProduct(ListItem* product);

	void UpdateProductNumbers(int idx);

	ListItem* SafeGetProduct(int idx);

	void SetCurrentListSubPage(ListProductsPages sub_page);

private:
	void OnProductClicked(ListItem* product);

	void set_list_size(int size);
	int get_list_size();

	Ui::ListSubPage *m_ui;
	ProductPage m_product_page;

	QString m_name;
	IdType m_id;

	int m_list_size;

private slots:
	// temporary plugs, should be reimplemented
	void OnAddProduct();
	void OnGoBack();
};
