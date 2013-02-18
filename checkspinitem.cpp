#include "checkspinitem.h"

CheckSpinItem::CheckSpinItem(QWidget *parent) :
    QWidget(parent)
{
    check = new QCheckBox;
    spin = new QSpinBox;
    layout = new QHBoxLayout;
    layout->addWidget(check);
    layout->addWidget(spin);
    setLayout(layout);

    connect(check,SIGNAL(toggled(bool)),this,SIGNAL(lengthToggled(bool)));
    connect(spin,SIGNAL(valueChanged(int)),this,SIGNAL(lengthChanged(int)));
}
