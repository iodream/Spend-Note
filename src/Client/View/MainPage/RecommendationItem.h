#pragma once

#include <QPushButton>
#include <QString>

namespace Ui {
class RecommendationItem;
}

class RecommendationItem : public QPushButton
{
	Q_OBJECT

public:
	explicit RecommendationItem(QString name, QWidget *parent = nullptr);
	~RecommendationItem();

	void Update();
	void SetNumber(int number);
	int m_number{1};

private:
	QString m_name;
	Ui::RecommendationItem *m_ui;
};
