#include "checkspinitem.h"

CheckSpinItem::CheckSpinItem(QWidget *parent) :
    QWidget(parent)
{
    check = new QCheckBox;
    spin = new QSpinBox;
    spin->setFixedWidth(40);
    layout = new QHBoxLayout;
    layout->addWidget(check);
    layout->addSpacing(5);
    layout->addWidget(spin);
    setLayout(layout);
layout->setMargin(5);
    connect(check,SIGNAL(toggled(bool)),this,SIGNAL(lengthToggled(bool)));
    connect(spin,SIGNAL(valueChanged(int)),this,SIGNAL(lengthChanged(int)));
}
