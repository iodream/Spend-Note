#pragma once

#include <QWidget>
#include <QString>
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
	int GetListSize();
	void SetListSize(int size);
	void enterEvent(QEnterEvent* event);
	void leaveEvent(QEvent* event);
private:
	static const int Transparency = 70;
	Ui::RecommendationWidget *m_ui;
	int m_list_size;
signals:
	void RecommendationClosed();

};
