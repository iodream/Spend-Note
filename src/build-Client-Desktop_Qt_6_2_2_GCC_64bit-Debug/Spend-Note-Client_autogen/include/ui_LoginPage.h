/********************************************************************************
** Form generated from reading UI file 'LoginPage.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINPAGE_H
#define UI_LOGINPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginPage
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QWidget *loginWidget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QFormLayout *formLayout;
    QLabel *loginLabel;
    QLineEdit *loginLineEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QLabel *loginErrorLabel;
    QPushButton *loginSubmitButton;
    QSpacerItem *verticalSpacer_3;
    QLabel *signupLabel;
    QPushButton *signupButton;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *LoginPage)
    {
        if (LoginPage->objectName().isEmpty())
            LoginPage->setObjectName(QString::fromUtf8("LoginPage"));
        LoginPage->resize(685, 701);
        gridLayout = new QGridLayout(LoginPage);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 93, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(91, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        loginWidget = new QWidget(LoginPage);
        loginWidget->setObjectName(QString::fromUtf8("loginWidget"));
        horizontalLayout_2 = new QHBoxLayout(loginWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(62, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        titleLabel = new QLabel(loginWidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        QFont font;
        font.setPointSize(24);
        titleLabel->setFont(font);
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel, 0, Qt::AlignHCenter);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetMinimumSize);
        loginLabel = new QLabel(loginWidget);
        loginLabel->setObjectName(QString::fromUtf8("loginLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, loginLabel);

        loginLineEdit = new QLineEdit(loginWidget);
        loginLineEdit->setObjectName(QString::fromUtf8("loginLineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, loginLineEdit);

        passwordLabel = new QLabel(loginWidget);
        passwordLabel->setObjectName(QString::fromUtf8("passwordLabel"));
        passwordLabel->setScaledContents(false);
        passwordLabel->setAlignment(Qt::AlignCenter);
        passwordLabel->setMargin(0);

        formLayout->setWidget(1, QFormLayout::LabelRole, passwordLabel);

        passwordLineEdit = new QLineEdit(loginWidget);
        passwordLineEdit->setObjectName(QString::fromUtf8("passwordLineEdit"));
        passwordLineEdit->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, passwordLineEdit);


        verticalLayout->addLayout(formLayout);

        loginErrorLabel = new QLabel(loginWidget);
        loginErrorLabel->setObjectName(QString::fromUtf8("loginErrorLabel"));
        loginErrorLabel->setStyleSheet(QString::fromUtf8("color: rgb(204, 0, 0);"));
        loginErrorLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(loginErrorLabel);

        loginSubmitButton = new QPushButton(loginWidget);
        loginSubmitButton->setObjectName(QString::fromUtf8("loginSubmitButton"));
        loginSubmitButton->setStyleSheet(QString::fromUtf8("color: rgb(243, 243, 243);\n"
"background-color: rgb(78, 154, 6);"));

        verticalLayout->addWidget(loginSubmitButton);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout->addItem(verticalSpacer_3);

        signupLabel = new QLabel(loginWidget);
        signupLabel->setObjectName(QString::fromUtf8("signupLabel"));
        signupLabel->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        verticalLayout->addWidget(signupLabel);

        signupButton = new QPushButton(loginWidget);
        signupButton->setObjectName(QString::fromUtf8("signupButton"));
        signupButton->setStyleSheet(QString::fromUtf8("background-color: rgb(78, 154, 6);\n"
"color: rgb(243, 243, 243);"));

        verticalLayout->addWidget(signupButton);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_4);

        verticalLayout->setStretch(0, 3);
        verticalLayout->setStretch(3, 1);
        verticalLayout->setStretch(4, 3);
        verticalLayout->setStretch(5, 1);
        verticalLayout->setStretch(6, 1);
        verticalLayout->setStretch(7, 2);

        horizontalLayout_2->addLayout(verticalLayout);

        horizontalSpacer_4 = new QSpacerItem(62, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 4);
        horizontalLayout_2->setStretch(2, 1);

        gridLayout->addWidget(loginWidget, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(91, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 93, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 2, 1, 1, 1);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(1, 5);
        gridLayout->setRowStretch(2, 1);
        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 5);
        gridLayout->setColumnStretch(2, 1);

        retranslateUi(LoginPage);

        QMetaObject::connectSlotsByName(LoginPage);
    } // setupUi

    void retranslateUi(QWidget *LoginPage)
    {
        LoginPage->setWindowTitle(QCoreApplication::translate("LoginPage", "Form", nullptr));
        titleLabel->setText(QCoreApplication::translate("LoginPage", "Spend & Note", nullptr));
        loginLabel->setText(QCoreApplication::translate("LoginPage", "Login", nullptr));
        loginLineEdit->setPlaceholderText(QCoreApplication::translate("LoginPage", "Login.....", nullptr));
        passwordLabel->setText(QCoreApplication::translate("LoginPage", "Password", nullptr));
        passwordLineEdit->setText(QString());
        passwordLineEdit->setPlaceholderText(QCoreApplication::translate("LoginPage", "Password.....", nullptr));
        loginErrorLabel->setText(QString());
        loginSubmitButton->setText(QCoreApplication::translate("LoginPage", "Submit", nullptr));
        signupLabel->setText(QCoreApplication::translate("LoginPage", "Do not have an account yet?", nullptr));
        signupButton->setText(QCoreApplication::translate("LoginPage", "Sign Up", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginPage: public Ui_LoginPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINPAGE_H
