#pragma once

#include <QPushButton>
#include <QString>

namespace Ui {
class RecommendationWidget;
}

class  : public QWidget
{
	Q_OBJECT

public:
	explicit RecommendationWidget(QWidget *parent = nullptr);
	~RecommendationWidget();

private:
	Ui::RecommendationWidget *m_ui;
};
