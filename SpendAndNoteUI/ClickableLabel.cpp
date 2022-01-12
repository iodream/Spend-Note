#include "ClickableLabel.h"

ClickableLabel::ClickableLabel(QWidget* parent, UIAuthorizedPages page)
{
    this->page = page;
}

void ClickableLabel::mousePressEvent(QMouseEvent* ev)
{
    emit MousePressed(this->page);
};
