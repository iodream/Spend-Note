#pragma once

#include <QPushButton>
#include <QString>
#include "Client/Entities/Entities.h"

namespace Ui {
class RecommendationItem;
}

class RecommendationItem : public QPushButton
{
	Q_OBJECT

public:
	explicit RecommendationItem(QString name, List list, QWidget *parent = nullptr);
	~RecommendationItem();

	void Update();
	void SetNumber(int number);
	List get_list() const { return m_list; }

	int m_number{1};

private:
	QString m_name;
	Ui::RecommendationItem *m_ui;
	List m_list;
};
