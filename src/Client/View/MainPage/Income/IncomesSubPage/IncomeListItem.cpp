#include "IncomeListItem.h"
#include "ui_IncomeListItem.h"

#include "View/Constants.h"
#include <QDate>
#include <QDateTime>
#include "View/MainPage/MainPage.h"

IncomeListItem::IncomeListItem(Income income, QWidget *parent)
	: QPushButton(parent)
	, m_income(income)
	, m_ui(new Ui::IncomeListItem)
{
	m_ui->setupUi(this);
}

IncomeListItem::~IncomeListItem()
{
	delete m_ui;
}

void IncomeListItem::changeEvent(QEvent* event)
{
	if(event)
	{
		switch(event->type())
		{
		case QEvent::LanguageChange:
			m_ui->retranslateUi(this);
			break;
		}

		QWidget::changeEvent(event);
	}
}

void IncomeListItem::UpdateColor()
{
	m_color = MainPage::ColorSettings::LIST_ACTIVE;
}

void IncomeListItem::Update()
{
	m_ui->Name->setText(m_income.name);
	QDateTime date = QDateTime::fromString(
	m_income.expiration_time, DATE_FORMAT_YYYY_MM_DD_HH_MM_SS);
	m_ui->ExpirationTime->setText(QLocale::system().toString(date, QLocale::system().dateTimeFormat()));
	m_ui->Amount->setText(QString::number(m_income.amount));
	m_ui->Category->setText(m_income.category.name);
	m_ui->Number->setText(QString("%1").arg(m_number));

	UpdateColor();
	setStyleSheet(
		QString("%1 %2;").arg(STYLESHEET_BACKGROUND_COLOR, m_color));
}

void IncomeListItem::set_number(int number)
{
	m_number = number;
	Update();
}

int IncomeListItem::get_number()
{
	return m_number;
}
