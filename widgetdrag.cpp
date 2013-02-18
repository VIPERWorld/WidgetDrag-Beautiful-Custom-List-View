#include "widgetdrag.h"
#include "ui_widgetdrag.h"
#include <QDebug>
#include <QDir>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    vwList = new QList<VariableWidget*>;
    lw = new MyListWidget(this);
    ui->verticalLayout->removeWidget(ui->addButton);
    ui->verticalLayout->addWidget(lw);
    ui->verticalLayout->addWidget(ui->addButton);

    for(quint8 i =0;i<3;i++)
    {
        addVariable();

    }
    connect(ui->addButton,SIGNAL(clicked()),this,SLOT(addVariable()));
    connect(lw,SIGNAL(itemMoved(int,int,QListWidgetItem*)),this,SLOT(resorted(int,int,QListWidgetItem*)));
    connect(lw,SIGNAL(itemRemoved(int)),this,SLOT(removed(int)));
    connect(lw,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(itemSelected(QListWidgetItem*)));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::nameChanged(QString newName)
{
    VariableWidget *vw = static_cast<VariableWidget*>(QObject::sender());
    int index = vwList->indexOf(vw);
    //    VariableWidget *vw = ui->listWidget->itemWidget(ui->listWidget->item());
}

void Widget::addVariable()
{
    VariableWidget *vw = new VariableWidget(this);
    vwList->append(vw);
    QIcon icon = QIcon::fromTheme("edit-undo",QIcon("../WidgetDrag/circle.png"));
    QListWidgetItem *item = new QListWidgetItem(lw);
//    item->setIcon(icon);
    lw->addItem(item);
    item->setSizeHint(vw->sizeHint());
    lw->setItemWidget(item,vw);
    connect(vw,SIGNAL(sizeToggled(QSize)),this,SLOT(itemSize(QSize)));
    connect(vw,SIGNAL(deleteVar()),this,SLOT(remVariable()));
}

void Widget::remVariable()
{
    VariableWidget *vw = static_cast<VariableWidget*>(QObject::sender());
    int row = vwList->indexOf(vw);
    QListWidgetItem *item = lw->item(row);
    lw->removeItemWidget(item);
    lw->takeItem(row);
    vwList->removeAt(row);
    delete vw;
}

void Widget::itemSize(QSize newSize)
{
    VariableWidget *vw = static_cast<VariableWidget*>(QObject::sender());
    int row = vwList->indexOf(vw);
    qDebug() << "row " << row << ", size: " << newSize.width() << " x " << newSize.height();
    QListWidgetItem *item = lw->item(row);
    item->setSizeHint(newSize);
    //    lw->item(vwList->indexOf(vw))->setSizeHint(vw->sizeHint());
}

//void Widget::resorted(QModelIndex sp,int ss,int se,QModelIndex dp,int dr, QPrivateSignal ps)
void Widget::resorted(int src,int dest,QListWidgetItem* item)
{
    VariableWidget *vw = static_cast<VariableWidget*>(lw->itemWidget(item));
    //    qDebug() << "resorted:";
    //    qDebug() << "item " << vw->getName() << "moved from row " << src << "to row " << dest;

    // Print list:
    //    for(int i=0;i<vwList->size();i++)
    //    {
    //        qDebug() << vwList->at(i)->getName();
    //    }
    // Resort in list:
    vwList->insert(dest, vwList->takeAt(src));
    //    qDebug() << "after resort:";
    //    for(int i=0;i<vwList->size();i++)
    //    {
    //        qDebug() << vwList->at(i)->getName();
    //    }
}

void Widget::removed(int row)
{
    // Print list:
    for(int i=0;i<vwList->size();i++)
    {
        qDebug() << vwList->at(i)->getName();
    }
    vwList->removeAt(row);
    for(int i=0;i<vwList->size();i++)
    {
        qDebug() << vwList->at(i)->getName();
    }
}

void Widget::differentRow(int row)
{
    qDebug() << "diff row";
}

void Widget::itemSelected(QListWidgetItem *item)
{
    //    VariableWidget *vw = static_cast<VariableWidget*>(lw->itemWidget(item));
    //    ui->lineEdit->setText(vw->getName());

    //    // print line
    //    int row = item->listWidget()->row(item);
    //    qDebug() << "row: " << row;
}
