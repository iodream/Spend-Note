/********************************************************************************
** Form generated from reading UI file 'MainPage.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINPAGE_H
#define UI_MAINPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainPage
{
public:
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QWidget *BalanceHolder;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QLabel *CurrentBalance;
    QSpacerItem *horizontalSpacer_2;
    QFrame *line;
    QSpacerItem *horizontalSpacer;
    QLabel *ProjectedBalance;
    QSpacerItem *horizontalSpacer_4;
    QStackedWidget *Display;
    QWidget *NavigationBar;
    QVBoxLayout *verticalLayout;
    QToolButton *GoToListsButton;
    QToolButton *toolButton_5;
    QToolButton *toolButton_3;
    QToolButton *toolButton_4;
    QToolButton *toolButton_2;
    QToolButton *LogoutButton;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *MainPage)
    {
        if (MainPage->objectName().isEmpty())
            MainPage->setObjectName(QString::fromUtf8("MainPage"));
        MainPage->resize(945, 654);
        gridLayout = new QGridLayout(MainPage);
        gridLayout->setSpacing(2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(2, 2, 2, 2);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        BalanceHolder = new QWidget(MainPage);
        BalanceHolder->setObjectName(QString::fromUtf8("BalanceHolder"));
        BalanceHolder->setMinimumSize(QSize(0, 40));
        BalanceHolder->setMaximumSize(QSize(16777215, 40));
        BalanceHolder->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout = new QHBoxLayout(BalanceHolder);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(16, 0, -1, 0);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        CurrentBalance = new QLabel(BalanceHolder);
        CurrentBalance->setObjectName(QString::fromUtf8("CurrentBalance"));
        CurrentBalance->setStyleSheet(QString::fromUtf8("color: black;"));
        CurrentBalance->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(CurrentBalance);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        line = new QFrame(BalanceHolder);
        line->setObjectName(QString::fromUtf8("line"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy);
        line->setMinimumSize(QSize(0, 0));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        ProjectedBalance = new QLabel(BalanceHolder);
        ProjectedBalance->setObjectName(QString::fromUtf8("ProjectedBalance"));
        ProjectedBalance->setStyleSheet(QString::fromUtf8("color: black;"));
        ProjectedBalance->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(ProjectedBalance);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        gridLayout_2->addWidget(BalanceHolder, 0, 0, 1, 1);

        Display = new QStackedWidget(MainPage);
        Display->setObjectName(QString::fromUtf8("Display"));

        gridLayout_2->addWidget(Display, 2, 0, 1, 1);


        gridLayout->addLayout(gridLayout_2, 0, 1, 1, 1);

        NavigationBar = new QWidget(MainPage);
        NavigationBar->setObjectName(QString::fromUtf8("NavigationBar"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(NavigationBar->sizePolicy().hasHeightForWidth());
        NavigationBar->setSizePolicy(sizePolicy1);
        NavigationBar->setMinimumSize(QSize(50, 0));
        NavigationBar->setMaximumSize(QSize(50, 16777215));
        NavigationBar->setLayoutDirection(Qt::LeftToRight);
        NavigationBar->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(NavigationBar);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        GoToListsButton = new QToolButton(NavigationBar);
        GoToListsButton->setObjectName(QString::fromUtf8("GoToListsButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(GoToListsButton->sizePolicy().hasHeightForWidth());
        GoToListsButton->setSizePolicy(sizePolicy2);
        GoToListsButton->setMinimumSize(QSize(50, 50));
        GoToListsButton->setAutoFillBackground(false);
        GoToListsButton->setStyleSheet(QString::fromUtf8("border-radius: 0px;\n"
"color: rgb(243, 243, 243);\n"
"background-color: black;"));

        verticalLayout->addWidget(GoToListsButton);

        toolButton_5 = new QToolButton(NavigationBar);
        toolButton_5->setObjectName(QString::fromUtf8("toolButton_5"));
        sizePolicy2.setHeightForWidth(toolButton_5->sizePolicy().hasHeightForWidth());
        toolButton_5->setSizePolicy(sizePolicy2);
        toolButton_5->setMinimumSize(QSize(50, 50));
        toolButton_5->setAutoFillBackground(false);
        toolButton_5->setStyleSheet(QString::fromUtf8("border-radius: 0px;\n"
"background-color: black;"));

        verticalLayout->addWidget(toolButton_5);

        toolButton_3 = new QToolButton(NavigationBar);
        toolButton_3->setObjectName(QString::fromUtf8("toolButton_3"));
        sizePolicy2.setHeightForWidth(toolButton_3->sizePolicy().hasHeightForWidth());
        toolButton_3->setSizePolicy(sizePolicy2);
        toolButton_3->setMinimumSize(QSize(50, 50));
        toolButton_3->setAutoFillBackground(false);
        toolButton_3->setStyleSheet(QString::fromUtf8("border-radius: 0px;\n"
"color: rgb(243, 243, 243);\n"
"background-color: black;"));

        verticalLayout->addWidget(toolButton_3);

        toolButton_4 = new QToolButton(NavigationBar);
        toolButton_4->setObjectName(QString::fromUtf8("toolButton_4"));
        toolButton_4->setEnabled(true);
        sizePolicy2.setHeightForWidth(toolButton_4->sizePolicy().hasHeightForWidth());
        toolButton_4->setSizePolicy(sizePolicy2);
        toolButton_4->setMinimumSize(QSize(50, 50));
        toolButton_4->setAutoFillBackground(false);
        toolButton_4->setStyleSheet(QString::fromUtf8("border-radius: 0px;\n"
"background-color: black;"));

        verticalLayout->addWidget(toolButton_4);

        toolButton_2 = new QToolButton(NavigationBar);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
        sizePolicy2.setHeightForWidth(toolButton_2->sizePolicy().hasHeightForWidth());
        toolButton_2->setSizePolicy(sizePolicy2);
        toolButton_2->setMinimumSize(QSize(50, 50));
        toolButton_2->setAutoFillBackground(false);
        toolButton_2->setStyleSheet(QString::fromUtf8("border-radius: 0px;\n"
"background-color: black;"));

        verticalLayout->addWidget(toolButton_2);

        LogoutButton = new QToolButton(NavigationBar);
        LogoutButton->setObjectName(QString::fromUtf8("LogoutButton"));
        sizePolicy2.setHeightForWidth(LogoutButton->sizePolicy().hasHeightForWidth());
        LogoutButton->setSizePolicy(sizePolicy2);
        LogoutButton->setMinimumSize(QSize(50, 50));
        LogoutButton->setAutoFillBackground(false);
        LogoutButton->setStyleSheet(QString::fromUtf8("border-radius: 0px;\n"
"color: rgb(243, 243, 243);\n"
"background-color: black;"));

        verticalLayout->addWidget(LogoutButton);

        verticalSpacer = new QSpacerItem(20, 16777215, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout->addItem(verticalSpacer);


        gridLayout->addWidget(NavigationBar, 0, 0, 1, 1, Qt::AlignLeft|Qt::AlignTop);


        retranslateUi(MainPage);

        Display->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainPage);
    } // setupUi

    void retranslateUi(QWidget *MainPage)
    {
        MainPage->setWindowTitle(QCoreApplication::translate("MainPage", "Form", nullptr));
        CurrentBalance->setText(QCoreApplication::translate("MainPage", "TextLabel", nullptr));
        ProjectedBalance->setText(QCoreApplication::translate("MainPage", "TextLabel", nullptr));
        GoToListsButton->setText(QCoreApplication::translate("MainPage", "Lists", nullptr));
        toolButton_5->setText(QCoreApplication::translate("MainPage", "...", nullptr));
        toolButton_3->setText(QCoreApplication::translate("MainPage", "...", nullptr));
        toolButton_4->setText(QCoreApplication::translate("MainPage", "...", nullptr));
        toolButton_2->setText(QCoreApplication::translate("MainPage", "...", nullptr));
        LogoutButton->setText(QCoreApplication::translate("MainPage", "Logout", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainPage: public Ui_MainPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINPAGE_H
