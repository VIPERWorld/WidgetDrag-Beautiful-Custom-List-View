#include "vectoropsitem.h"

VectorOpsItem::VectorOpsItem(QWidget *parent) :
    QWidget(parent)
{
    upButton = new QPushButton("U");
    downButton = new QPushButton("D");
    delButton = new QPushButton("X");
    layout = new QHBoxLayout;
    layout->addWidget(upButton);
    layout->addWidget(downButton);
    layout->addWidget(delButton);
    setLayout(layout);

    connect(upButton,SIGNAL(clicked()),this,SIGNAL(moveUp()));
    connect(downButton,SIGNAL(clicked()),this,SIGNAL(moveDown()));
    connect(delButton,SIGNAL(clicked()),this,SIGNAL(removeVar()));
}
