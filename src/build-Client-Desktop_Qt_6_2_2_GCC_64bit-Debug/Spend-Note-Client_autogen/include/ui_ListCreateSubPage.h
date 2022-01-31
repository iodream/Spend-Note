/********************************************************************************
** Form generated from reading UI file 'ListCreateSubPage.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTCREATESUBPAGE_H
#define UI_LISTCREATESUBPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ListCreateSubPage
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *GoBackButton;
    QPushButton *SaveButton;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_2;

    void setupUi(QWidget *ListCreateSubPage)
    {
        if (ListCreateSubPage->objectName().isEmpty())
            ListCreateSubPage->setObjectName(QString::fromUtf8("ListCreateSubPage"));
        ListCreateSubPage->resize(389, 317);
        gridLayout = new QGridLayout(ListCreateSubPage);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        GoBackButton = new QPushButton(ListCreateSubPage);
        GoBackButton->setObjectName(QString::fromUtf8("GoBackButton"));

        horizontalLayout_3->addWidget(GoBackButton);

        SaveButton = new QPushButton(ListCreateSubPage);
        SaveButton->setObjectName(QString::fromUtf8("SaveButton"));

        horizontalLayout_3->addWidget(SaveButton);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(ListCreateSubPage);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(80, 0));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(ListCreateSubPage);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));

        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(ListCreateSubPage);

        QMetaObject::connectSlotsByName(ListCreateSubPage);
    } // setupUi

    void retranslateUi(QWidget *ListCreateSubPage)
    {
        ListCreateSubPage->setWindowTitle(QCoreApplication::translate("ListCreateSubPage", "Form", nullptr));
        GoBackButton->setText(QCoreApplication::translate("ListCreateSubPage", "Go Back", nullptr));
        SaveButton->setText(QCoreApplication::translate("ListCreateSubPage", "Save", nullptr));
        label->setText(QCoreApplication::translate("ListCreateSubPage", "List name:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ListCreateSubPage: public Ui_ListCreateSubPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTCREATESUBPAGE_H
