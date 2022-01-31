/********************************************************************************
** Form generated from reading UI file 'ListsSubPage.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTSSUBPAGE_H
#define UI_LISTSSUBPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ListsSubPage
{
public:
    QGridLayout *gridLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QWidget *NameHolder;
    QHBoxLayout *horizontalLayout_2;
    QFrame *line;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLabel *ListSize;
    QPushButton *AddItemButton;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *Items;
    QVBoxLayout *ItemsLayout;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *ListsSubPage)
    {
        if (ListsSubPage->objectName().isEmpty())
            ListsSubPage->setObjectName(QString::fromUtf8("ListsSubPage"));
        ListsSubPage->resize(887, 602);
        gridLayout = new QGridLayout(ListsSubPage);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        frame = new QFrame(ListsSubPage);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setStyleSheet(QString::fromUtf8("background-color: #a3ffbc;"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(16, 0, 9, 0);
        NameHolder = new QWidget(frame);
        NameHolder->setObjectName(QString::fromUtf8("NameHolder"));
        NameHolder->setMinimumSize(QSize(200, 0));
        horizontalLayout_2 = new QHBoxLayout(NameHolder);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));

        horizontalLayout->addWidget(NameHolder);

        line = new QFrame(frame);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        widget = new QWidget(frame);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        ListSize = new QLabel(widget);
        ListSize->setObjectName(QString::fromUtf8("ListSize"));
        ListSize->setMinimumSize(QSize(25, 0));

        horizontalLayout_3->addWidget(ListSize);

        AddItemButton = new QPushButton(widget);
        AddItemButton->setObjectName(QString::fromUtf8("AddItemButton"));
        AddItemButton->setMinimumSize(QSize(40, 0));

        horizontalLayout_3->addWidget(AddItemButton);


        horizontalLayout->addWidget(widget);


        gridLayout->addWidget(frame, 1, 0, 1, 1);

        stackedWidget = new QStackedWidget(ListsSubPage);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        page->setLayoutDirection(Qt::LeftToRight);
        verticalLayout = new QVBoxLayout(page);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea = new QScrollArea(page);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        Items = new QWidget();
        Items->setObjectName(QString::fromUtf8("Items"));
        Items->setGeometry(QRect(0, 0, 849, 513));
        ItemsLayout = new QVBoxLayout(Items);
        ItemsLayout->setObjectName(QString::fromUtf8("ItemsLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        ItemsLayout->addItem(verticalSpacer);

        scrollArea->setWidget(Items);

        verticalLayout->addWidget(scrollArea);

        stackedWidget->addWidget(page);

        gridLayout->addWidget(stackedWidget, 2, 0, 1, 1);


        retranslateUi(ListsSubPage);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ListsSubPage);
    } // setupUi

    void retranslateUi(QWidget *ListsSubPage)
    {
        ListsSubPage->setWindowTitle(QCoreApplication::translate("ListsSubPage", "Form", nullptr));
        label->setText(QCoreApplication::translate("ListsSubPage", "Items:", nullptr));
        ListSize->setText(QString());
        AddItemButton->setText(QCoreApplication::translate("ListsSubPage", "Add", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ListsSubPage: public Ui_ListsSubPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTSSUBPAGE_H
