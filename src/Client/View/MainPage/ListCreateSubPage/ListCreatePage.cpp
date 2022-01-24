#include "ListCreatePage.h"
#include "ui_ListCreatePage.h"
#include "Exception.h"

ListCreatePage::ListCreatePage(QWidget *parent)
	: QWidget(parent)
	, m_ui(new Ui::ListCreatePage)
{
	m_ui->setupUi(this);
	//m_ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//connect(m_ui->Updatebutton, SIGNAL(released()), this, SLOT(Update()));

	connect(
		m_ui->goBackButton,
		SIGNAL(clicked()),
		this,
		SLOT(OnGoBackClicked()));
}



ListCreatePage::~ListCreatePage()
{
	delete m_ui;
}


void ListCreatePage::OnGoBackClicked()
{
	emit GoBack();
}

