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
    variableList = new QList<ComplexVariable*>;
    lw = new MyListWidget(this);
    ui->verticalLayout->addWidget(lw);

    for(quint8 i =0;i<1;i++)
    {
        addVariable();

    }
    connect(ui->addByteButton,SIGNAL(clicked()),this,SLOT(addVariable()));
    connect(ui->addNumberButton,SIGNAL(clicked()),this,SLOT(addVariable()));
    connect(ui->addVectorButton,SIGNAL(clicked()),this,SLOT(addVariable()));
    connect(lw,SIGNAL(itemMoved(int,int,QListWidgetItem*)),this,SLOT(resorted(int,int,QListWidgetItem*)));
    connect(lw,SIGNAL(itemRemoved(int)),this,SLOT(itemRemoved(int)));
    connect(lw,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(itemSelected(QListWidgetItem*)));
    connect(ui->printListButton,SIGNAL(clicked()),this,SLOT(printList()));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::variableListChanged()
{
    printList();
    emit updateVariableList();
}


void Widget::nameChanged(QString newName)
{
    VariableWidget *vw = static_cast<VariableWidget*>(QObject::sender());
    int index = vwList->indexOf(vw);
}

void Widget::typeChanged(int newType)
{
    VariableWidget *vw = static_cast<VariableWidget*>(QObject::sender());
    int index = vwList->indexOf(vw);
}


void Widget::lengthToggled(bool fixed)
{
    VariableWidget *vw = static_cast<VariableWidget*>(QObject::sender());
    int index = vwList->indexOf(vw);
}

void Widget::lengthChanged(int newLength)
{
    VariableWidget *vw = static_cast<VariableWidget*>(QObject::sender());
    int index = vwList->indexOf(vw);
}

void Widget::matchToggled(bool matched)
{
    VariableWidget *vw = static_cast<VariableWidget*>(QObject::sender());
    int index = vwList->indexOf(vw);
}

void Widget::matchChanged(QString newMatch)
{
    VariableWidget *vw = static_cast<VariableWidget*>(QObject::sender());
    int index = vwList->indexOf(vw);
}

void Widget::repeatChanged(int newRepeat)
{
    VariableWidget *vw = static_cast<VariableWidget*>(QObject::sender());
    int index = vwList->indexOf(vw);
}

void Widget::addVariable()
{
    QPushButton *senderButton = static_cast<QPushButton*>(QObject::sender());
    VariableWidget *vw = new VariableWidget(lw);
    if(senderButton==ui->addNumberButton)
    {
        vw->setNumber();
    }
    else if(senderButton==ui->addVectorButton)
    {
        vw->setVector();
    }

    vwList->append(vw);
    variableList->append(vw->variable);
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
    connect(vw,SIGNAL(variableChanged()),this,SLOT(variableListChanged()));
    variableListChanged();

}

void Widget::remVariable()
{
    VariableWidget *vw = static_cast<VariableWidget*>(QObject::sender());
    int row = vwList->indexOf(vw);
    QListWidgetItem *item = lw->item(row);
    variableList->removeAt(row);
    lw->removeItemWidget(item);
    lw->takeItem(row);
    vwList->removeAt(row);
    delete vw;
    variableListChanged();
}

void Widget::itemSize(QSize newSize)
{
    VariableWidget *vw = static_cast<VariableWidget*>(QObject::sender());
    int row = vwList->indexOf(vw);
    QListWidgetItem *item = lw->item(row);
    item->setSizeHint(newSize);
}

void Widget::resorted(int src,int dest,QListWidgetItem* item)
{
    VariableWidget *vw = static_cast<VariableWidget*>(lw->itemWidget(item));

    // Resort in list:
    vwList->insert(dest, vwList->takeAt(src));
    variableList->insert(dest,variableList->takeAt(src));
    variableListChanged();
}

void Widget::itemRemoved(int row)
{
    variableList->removeAt(row);
    delete vwList->at(row);
    vwList->removeAt(row);
    variableListChanged();
}

void Widget::itemSelected(QListWidgetItem *item)
{

}

void Widget::printList()
{
    foreach(ComplexVariable *item, *variableList)
    {
        QString outString = item->name;
        outString.append("| type: ");
        switch(item->type)
        {
        case BYTTYPE:
            outString.append("byt, ");
            break;
        case NUMTYPE:
            outString.append("num, ");
            break;
        default:
            outString.append("vec, rep: ");
            outString.append(QString("%1:\n").arg(item->repeat));
            // Print vector contents
            foreach(BaseVariable *vecItem, *item->vector)
            {
                outString.append("\t");
                outString.append(vecItem->name);
                outString.append("| ");
                // Type
                if(vecItem->type==BYTTYPE)
                {
                    outString.append("byt, ");
                }
                else
                {
                    outString.append("num, ");
                }
                // Length
                if(vecItem->fixed)
                {
                    outString.append("length: fix, ");
                    outString.append(QString("len_val: %1, ").arg(vecItem->length));
                }
                else
                {
                    outString.append("length: var, ");
                }
                // Match
                if(vecItem->match)
                {
                    outString.append("match: yes: , ");
                    outString.append(vecItem->matchBytes);
                }
                else
                {
                    outString.append("match: no");
                }
                outString.append("\n");
            }

            break;
        }
        if(item->type!=VECTYPE)
        {
            if(item->fixed)
            {
                outString.append("length: fix, ");
                outString.append(QString("len_val: %1, ").arg(item->length));
            }
            else
            {
                outString.append("length: var, ");
            }

            if(item->match)
            {
                outString.append("match: yes: ");
                outString.append(item->matchBytes);
            }
            else
            {
                outString.append("match: no");
            }
        }
        qDebug() << outString;
    }
    qDebug() << "===";
}
