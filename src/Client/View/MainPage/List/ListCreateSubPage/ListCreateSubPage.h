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
	void FillStateBox(const std::vector<ListState>& states);

signals:
	void GoBack(int n=1);
	void CreateList();

private:
	Ui::ListCreateSubPage *m_ui;
};
