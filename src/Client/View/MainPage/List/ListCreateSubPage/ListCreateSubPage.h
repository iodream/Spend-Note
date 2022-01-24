#pragma once

#include <QString>
#include <QWidget>

#include "Common.h"

namespace Ui {
class ListCreateSubPage;
}

class ListCreateSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit ListCreateSubPage(QWidget *parent=nullptr);
	~ListCreateSubPage();

signals:
	void GoBack();
	void CreateList();

private:
	Ui::ListCreateSubPage *m_ui;
};
