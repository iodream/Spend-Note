#pragma once

#include <QWidget>
#include "RecommendationItem.h"

namespace Ui {
class RecommendationWidget;
}

class RecommendationWidget : public QWidget
{
	Q_OBJECT

public:
	explicit RecommendationWidget(QWidget *parent = nullptr);
	~RecommendationWidget();

	void AppendItem(RecommendationItem* Item);
	void InsertItem(RecommendationItem* Item, int idx);
	void RemoveItem();

	int GetListSize();
	void SetListSize(int size);

private:
	Ui::RecommendationWidget *m_ui;
	int m_list_size;

signals:
	void RecommendationClosed();
};
