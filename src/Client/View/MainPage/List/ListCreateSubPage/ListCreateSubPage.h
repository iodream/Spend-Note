#pragma once

#include <QString>
#include <QWidget>

#include "Common.h"
#include "Entities/Entities.h"

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
	void Update();
signals:
	void CreateList();

private:
	Ui::ListCreateSubPage *m_ui;
};
