/********************************************************************************
** Form generated from reading UI file 'SignupPage.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUPPAGE_H
#define UI_SIGNUPPAGE_H

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

class Ui_SignupPage
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QWidget *signupWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *signupTitleLabel;
    QFormLayout *formLayout_2;
    QLabel *usernameLabel;
    QLineEdit *usernameLineEdit;
    QLabel *passwordCreateLabel;
    QLineEdit *passwordCreateLineEdit;
    QLabel *passwordRepeatLabel;
    QLineEdit *passwordRepeatLineEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *GoBackButton;
    QPushButton *signupSubmitButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *SignupPage)
    {
        if (SignupPage->objectName().isEmpty())
            SignupPage->setObjectName(QString::fromUtf8("SignupPage"));
        SignupPage->resize(469, 616);
        gridLayout = new QGridLayout(SignupPage);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 81, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(60, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        signupWidget = new QWidget(SignupPage);
        signupWidget->setObjectName(QString::fromUtf8("signupWidget"));
        verticalLayout_2 = new QVBoxLayout(signupWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        signupTitleLabel = new QLabel(signupWidget);
        signupTitleLabel->setObjectName(QString::fromUtf8("signupTitleLabel"));
        signupTitleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(signupTitleLabel);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        usernameLabel = new QLabel(signupWidget);
        usernameLabel->setObjectName(QString::fromUtf8("usernameLabel"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, usernameLabel);

        usernameLineEdit = new QLineEdit(signupWidget);
        usernameLineEdit->setObjectName(QString::fromUtf8("usernameLineEdit"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, usernameLineEdit);

        passwordCreateLabel = new QLabel(signupWidget);
        passwordCreateLabel->setObjectName(QString::fromUtf8("passwordCreateLabel"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, passwordCreateLabel);

        passwordCreateLineEdit = new QLineEdit(signupWidget);
        passwordCreateLineEdit->setObjectName(QString::fromUtf8("passwordCreateLineEdit"));
        passwordCreateLineEdit->setEchoMode(QLineEdit::Password);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, passwordCreateLineEdit);

        passwordRepeatLabel = new QLabel(signupWidget);
        passwordRepeatLabel->setObjectName(QString::fromUtf8("passwordRepeatLabel"));
        passwordRepeatLabel->setMinimumSize(QSize(107, 0));
        passwordRepeatLabel->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);

        formLayout_2->setWidget(2, QFormLayout::LabelRole, passwordRepeatLabel);

        passwordRepeatLineEdit = new QLineEdit(signupWidget);
        passwordRepeatLineEdit->setObjectName(QString::fromUtf8("passwordRepeatLineEdit"));
        passwordRepeatLineEdit->setEchoMode(QLineEdit::Password);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, passwordRepeatLineEdit);


        verticalLayout_2->addLayout(formLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        GoBackButton = new QPushButton(signupWidget);
        GoBackButton->setObjectName(QString::fromUtf8("GoBackButton"));

        horizontalLayout->addWidget(GoBackButton);

        signupSubmitButton = new QPushButton(signupWidget);
        signupSubmitButton->setObjectName(QString::fromUtf8("signupSubmitButton"));
        signupSubmitButton->setStyleSheet(QString::fromUtf8("background-color: rgb(78, 154, 6);"));
        signupSubmitButton->setFlat(false);

        horizontalLayout->addWidget(signupSubmitButton);


        verticalLayout_2->addLayout(horizontalLayout);


        gridLayout->addWidget(signupWidget, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(60, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 81, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 2, 1, 1, 1);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(1, 5);
        gridLayout->setRowStretch(2, 1);
        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 5);
        gridLayout->setColumnStretch(2, 1);

        retranslateUi(SignupPage);

        QMetaObject::connectSlotsByName(SignupPage);
    } // setupUi

    void retranslateUi(QWidget *SignupPage)
    {
        SignupPage->setWindowTitle(QCoreApplication::translate("SignupPage", "Form", nullptr));
        signupTitleLabel->setText(QCoreApplication::translate("SignupPage", "<html><head/><body><p><span style=\" font-size:24pt;\">Registration</span></p></body></html>", nullptr));
        usernameLabel->setText(QCoreApplication::translate("SignupPage", "Create a username:", nullptr));
        usernameLineEdit->setText(QString());
        usernameLineEdit->setPlaceholderText(QCoreApplication::translate("SignupPage", "Type your username", nullptr));
        passwordCreateLabel->setText(QCoreApplication::translate("SignupPage", "Create a password:", nullptr));
        passwordCreateLineEdit->setPlaceholderText(QCoreApplication::translate("SignupPage", "Create password...", nullptr));
        passwordRepeatLabel->setText(QCoreApplication::translate("SignupPage", "Repeat password:", nullptr));
        passwordRepeatLineEdit->setPlaceholderText(QCoreApplication::translate("SignupPage", "Repeat password...", nullptr));
        GoBackButton->setText(QCoreApplication::translate("SignupPage", "Go back", nullptr));
        signupSubmitButton->setText(QCoreApplication::translate("SignupPage", "Submit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SignupPage: public Ui_SignupPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUPPAGE_H
