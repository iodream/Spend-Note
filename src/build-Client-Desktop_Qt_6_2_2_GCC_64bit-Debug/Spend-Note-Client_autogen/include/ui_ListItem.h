/********************************************************************************
** Form generated from reading UI file 'ListItem.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTITEM_H
#define UI_LISTITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ListItem
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *Holder;
    QHBoxLayout *horizontalLayout_2;
    QLabel *Number;
    QFrame *line;
    QWidget *ListNameHolder;
    QGridLayout *gridLayout;
    QLabel *ListName;
    QSpacerItem *horizontalSpacer_3;
    QFrame *line_2;
    QWidget *ItemsHolder;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QLabel *Items;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *ListItem)
    {
        if (ListItem->objectName().isEmpty())
            ListItem->setObjectName(QString::fromUtf8("ListItem"));
        ListItem->resize(344, 50);
        ListItem->setMinimumSize(QSize(0, 50));
        ListItem->setMaximumSize(QSize(16777215, 50));
        horizontalLayout = new QHBoxLayout(ListItem);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        Holder = new QWidget(ListItem);
        Holder->setObjectName(QString::fromUtf8("Holder"));
        Holder->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_2 = new QHBoxLayout(Holder);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(3, 0, 9, 0);
        Number = new QLabel(Holder);
        Number->setObjectName(QString::fromUtf8("Number"));
        Number->setMinimumSize(QSize(25, 0));
        Number->setMaximumSize(QSize(25, 16777215));
        Number->setStyleSheet(QString::fromUtf8("background: transparent;"));
        Number->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(Number);

        line = new QFrame(Holder);
        line->setObjectName(QString::fromUtf8("line"));
        line->setMaximumSize(QSize(2, 36));
        line->setStyleSheet(QString::fromUtf8(""));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line);

        ListNameHolder = new QWidget(Holder);
        ListNameHolder->setObjectName(QString::fromUtf8("ListNameHolder"));
        ListNameHolder->setStyleSheet(QString::fromUtf8("background: transparent;"));
        gridLayout = new QGridLayout(ListNameHolder);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        ListName = new QLabel(ListNameHolder);
        ListName->setObjectName(QString::fromUtf8("ListName"));
        ListName->setMinimumSize(QSize(200, 0));
        QFont font;
        font.setPointSize(12);
        ListName->setFont(font);
        ListName->setStyleSheet(QString::fromUtf8("background: transparent;"));

        gridLayout->addWidget(ListName, 0, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 1, 1, 1);


        horizontalLayout_2->addWidget(ListNameHolder);

        line_2 = new QFrame(Holder);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line_2);

        ItemsHolder = new QWidget(Holder);
        ItemsHolder->setObjectName(QString::fromUtf8("ItemsHolder"));
        ItemsHolder->setStyleSheet(QString::fromUtf8("background: transparent;"));
        horizontalLayout_3 = new QHBoxLayout(ItemsHolder);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, -1, -1, -1);
        horizontalSpacer = new QSpacerItem(42, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        Items = new QLabel(ItemsHolder);
        Items->setObjectName(QString::fromUtf8("Items"));
        QFont font1;
        font1.setPointSize(13);
        Items->setFont(font1);
        Items->setStyleSheet(QString::fromUtf8("background: transparent;"));

        horizontalLayout_3->addWidget(Items);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        horizontalLayout_2->addWidget(ItemsHolder);


        horizontalLayout->addWidget(Holder);


        retranslateUi(ListItem);

        QMetaObject::connectSlotsByName(ListItem);
    } // setupUi

    void retranslateUi(QWidget *ListItem)
    {
        ListItem->setWindowTitle(QCoreApplication::translate("ListItem", "Form", nullptr));
        Number->setText(QCoreApplication::translate("ListItem", "0", nullptr));
        ListName->setText(QCoreApplication::translate("ListItem", "ListName", nullptr));
        Items->setText(QCoreApplication::translate("ListItem", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ListItem: public Ui_ListItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTITEM_H
