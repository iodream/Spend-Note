#pragma once

#include <QWidget>
#include <QPushButton>
#include <QString>

namespace Ui {
class ListsItem;
}

namespace {
const QString ITEM_COLOR_YES  = "rgba(168, 232, 39, 50%)";
const QString ITEM_COLOR_NO = "rgba(235, 235, 235, 50%)";
}

class ListsItem : public QPushButton
{
	Q_OBJECT

public:
	using IdType = int;

	explicit ListsItem(int id, const QString& listName, const QString& Status, QWidget *parent);
	~ListsItem();
	Ui::ListsItem *m_ui;

private:
	IdType m_id;
	QString m_name;
	QString m_color;
};
