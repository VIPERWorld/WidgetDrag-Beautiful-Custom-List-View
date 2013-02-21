#include "vectoritemwidget.h"

VectorItemWidget::VectorItemWidget(QWidget *parent) :
    QWidget(parent)
{
    nameEdit = new QLineEdit("variable1");
    typeButton = new QPushButton("A");
    hLayout = new QHBoxLayout;
    hLayout->addWidget(nameEdit);
    hLayout->addWidget(typeButton);
    setLayout(hLayout);
}
