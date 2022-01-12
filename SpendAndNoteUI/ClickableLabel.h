#pragma once

#include <QLabel>
#include <QWidget>
#include <QMouseEvent>
#include <QEvent>
#include <QDebug>

#include "Constants.h"

class ClickableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ClickableLabel(QWidget* parent = 0, UIAuthorizedPages page = UIAuthorizedPages::MAIN);

    void mousePressEvent(QMouseEvent* ev);

    UIAuthorizedPages page;

signals:
    void MousePressed(UIAuthorizedPages page);

};
