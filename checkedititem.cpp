#include "checkedititem.h"

CheckEditItem::CheckEditItem(QWidget *parent) :
    QWidget(parent)
{
    check = new QCheckBox;
    edit = new QLineEdit;
    edit->setMinimumWidth(40);
    layout = new QHBoxLayout;
    layout->addWidget(check);
    layout->addWidget(edit);
    setLayout(layout);
}
