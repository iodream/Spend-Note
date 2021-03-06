#include "ProductItem.h"
#include "ui_ProductItem.h"

#include "View/Constants.h"

#include "View/MainPage/MainPage.h"

ProductItem::ProductItem(Product product, QWidget *parent)
	: QPushButton(parent)
	, m_product(product)
	, m_ui(new Ui::ProductItem)
{
	m_ui->setupUi(this);
}

ProductItem::~ProductItem()
{
	delete m_ui;
}

void ProductItem::UpdateColor()
{
	switch(m_product.priority)
	{
	case 1:
		m_color = MainPage::ColorSettings::PRODUCT_PRIO1;
		break;
	case 2:
		m_color = MainPage::ColorSettings::PRODUCT_PRIO2;
		break;
	case 3:
		m_color = MainPage::ColorSettings::PRODUCT_PRIO3;
		break;
	case 4:
		m_color = MainPage::ColorSettings::PRODUCT_PRIO4;
		break;
	case 5:
		m_color = MainPage::ColorSettings::PRODUCT_PRIO5;
		break;
	}
}


void ProductItem::changeEvent(QEvent* event)
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

void ProductItem::HideCheck()
{
	m_ui->PurchasedCheckbox->setHidden(true);
}

void ProductItem::SetText(const QString& text)
{
	m_ui->Number->setText(text);
}

void ProductItem::Update()
{
	m_ui->ProductName->setText(m_product.name);
	QDateTime date = QDateTime::fromString(
		m_product.buy_until_date, DATE_FORMAT_YYYY_MM_DD_HH_MM_SS);
	m_ui->BuyUntil->setText(QLocale::system().toString(date, QLocale::system().dateTimeFormat()));
	m_ui->Price->setText(QString("%1").arg(m_product.price));
	m_ui->Number->setText(QString("%1").arg(m_number));
	m_ui->PurchasedCheckbox->setChecked(m_product.is_bought);
	UpdateColor();
	if(m_product.is_bought)
		m_ui->PurchasedCheckbox->setChecked(true);
	else
		m_ui->PurchasedCheckbox->setChecked(false);
	setStyleSheet(
		QString("%1 %2;").arg(STYLESHEET_BACKGROUND_COLOR, m_color));
}

void ProductItem::set_number(int number)
{
	m_number = number;
	Update();
}

int ProductItem::get_number()
{
	return m_number;
}

QString ProductItem::get_color()
{
	return m_color;
}
