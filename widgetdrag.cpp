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

    for(quint8 i =0;i<1;i++)
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
    qDebug() << "variable " << index << "has changed name to " << newName;
}

void Widget::typeChanged(int newType)
{
    VariableWidget *vw = static_cast<VariableWidget*>(QObject::sender());
    int index = vwList->indexOf(vw);

    QString type;
    switch(newType)
    {
    case BYTTYPE:
        type = "byte";
        break;
    case NUMTYPE:
        type = "number";
        break;
    default:
        type = "vector";
        break;
    }
    qDebug() << "variable " << index << "has changed type to " << type;
}


void Widget::lengthToggled(bool fixed)
{
    VariableWidget *vw = static_cast<VariableWidget*>(QObject::sender());
    int index = vwList->indexOf(vw);
    qDebug() << "variable " << index << "has set fixed length to " << fixed;
}

void Widget::lengthChanged(int newLength)
{
    VariableWidget *vw = static_cast<VariableWidget*>(QObject::sender());
    int index = vwList->indexOf(vw);
    qDebug() << "variable " << index << "has set the fixed length to" << newLength;
}

void Widget::matchToggled(bool matched)
{
    VariableWidget *vw = static_cast<VariableWidget*>(QObject::sender());
    int index = vwList->indexOf(vw);
    qDebug() << "variable " << index << "has set match to " << matched;
}

void Widget::matchChanged(QString newMatch)
{
    VariableWidget *vw = static_cast<VariableWidget*>(QObject::sender());
    int index = vwList->indexOf(vw);
    qDebug() << "variable " << index << "has set string to match to" << newMatch;
}

void Widget::repeatChanged(int newRepeat)
{
    VariableWidget *vw = static_cast<VariableWidget*>(QObject::sender());
    int index = vwList->indexOf(vw);
    qDebug() << "variable " << index << "has set the vector repetitions to" << newRepeat;
}

void Widget::addVariable()
{
    VariableWidget *vw = new VariableWidget(lw);
    vwList->append(vw);
    QListWidgetItem *item = new QListWidgetItem(lw);

    lw->addItem(item);
    item->setSizeHint(vw->sizeHint());
    lw->setItemWidget(item,vw);

    connect(vw,SIGNAL(nameChange(QString)),this,SLOT(nameChanged(QString)));
    connect(vw,SIGNAL(typeChange(int)),this,SLOT(typeChanged(int)));
    connect(vw,SIGNAL(lengthToggle(bool)),this,SLOT(lengthToggled(bool)));
    connect(vw,SIGNAL(lengthChange(int)),this,SLOT(lengthChanged(int)));
    connect(vw,SIGNAL(matchToggle(bool)),this,SLOT(matchToggled(bool)));
    connect(vw,SIGNAL(matchChange(QString)),this,SLOT(matchChanged(QString)));
    connect(vw,SIGNAL(repeatChange(int)),this,SLOT(repeatChanged(int)));

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
}

//void Widget::resorted(QModelIndex sp,int ss,int se,QModelIndex dp,int dr, QPrivateSignal ps)
void Widget::resorted(int src,int dest,QListWidgetItem* item)
{
    VariableWidget *vw = static_cast<VariableWidget*>(lw->itemWidget(item));

    // Resort in list:
    vwList->insert(dest, vwList->takeAt(src));
}

void Widget::removed(int row)
{
    // Print list:
    for(int i=0;i<vwList->size();i++)
    {
//        qDebug() << vwList->at(i)->getName();
    }
    vwList->removeAt(row);
    for(int i=0;i<vwList->size();i++)
    {
//        qDebug() << vwList->at(i)->getName();
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
