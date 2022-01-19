#include "SettingsSubPage.h"
#include "ui_SettingsSubPage.h"

SettingsSubPage::SettingsSubPage(QWidget *parent) :
	QWidget(parent),
	m_ui(new Ui::SettingsSubPage)
{
	m_ui->setupUi(this);

	connect(m_ui->logoutButton, SIGNAL(clicked())
			, this, SLOT(OnLogoutButtonClicked()));
}

SettingsSubPage::~SettingsSubPage()
{
	delete m_ui;
}

void SettingsSubPage::OnLogoutButtonClicked()
{
	emit Logout();
}
