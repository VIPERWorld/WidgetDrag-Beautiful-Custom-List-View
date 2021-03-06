#include "widgetdrag.h"
#include <QDebug>
#include <QDir>

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
// Assets
    addByteIconPixmap = QPixmap("../WidgetDrag/addbyte_icon.png");
    addNumberIconPixmap = QPixmap("../WidgetDrag/addnumber_icon.png");
    addVectorIconPixmap = QPixmap("../WidgetDrag/addvector_icon.png");
    moreIconPixmap = QPixmap("../WidgetDrag/more_icon.png");
    lessIconPixmap = QPixmap("../WidgetDrag/less_icon.png");

    expanded=true;

    nameEdit = new QLineEdit("Parser 001");
    nameEdit->setFixedHeight(24);
    addByteButton = new QPushButton;
    addByteButton->setFixedHeight(24);
    addByteButton->setFixedWidth(24);
    addByteButton->setIcon(QIcon(addByteIconPixmap));
    addNumberButton = new QPushButton;
    addNumberButton->setFixedHeight(24);
    addNumberButton->setFixedWidth(24);
    addNumberButton->setIcon(QIcon(addNumberIconPixmap));
    addVectorButton = new QPushButton;
    addVectorButton->setFixedHeight(24);
    addVectorButton->setFixedWidth(24);
    addVectorButton->setIcon(QIcon(addVectorIconPixmap));
    expandButton = new QPushButton;
    expandButton->setFixedSize(24,24);
    expandButton->setIcon(QIcon(moreIconPixmap));

    vwList = new QList<VariableWidget*>;
    variableList = new QList<ComplexVariable*>;
    lw = new LiveListWidget(this);

    for(quint8 i =0;i<1;i++)
    {
        addVariable();

    }

    controlLayout = new QHBoxLayout;
controlLayout->addWidget(nameEdit);
    controlLayout->addWidget(addByteButton);
    controlLayout->addWidget(addNumberButton);
    controlLayout->addWidget(addVectorButton);
    controlLayout->addWidget(expandButton);

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(controlLayout);
    mainLayout->addWidget(lw);
    setLayout(mainLayout);
    setMinimumWidth(500);

    connect(addByteButton,SIGNAL(clicked()),this,SLOT(addVariable()));
    connect(addNumberButton,SIGNAL(clicked()),this,SLOT(addVariable()));
    connect(addVectorButton,SIGNAL(clicked()),this,SLOT(addVariable()));
    connect(expandButton,SIGNAL(clicked()),this,SLOT(toggleExpand()));
    connect(lw,SIGNAL(itemMoved(int,int,QListWidgetItem*)),this,SLOT(resorted(int,int,QListWidgetItem*)));
    connect(lw,SIGNAL(itemRemoved(int)),this,SLOT(itemRemoved(int)));
//    connect(ui->printListButton,SIGNAL(clicked()),this,SLOT(printList()));

    // Styling
    QFile qss("../WidgetDrag/widgetdrag.css");
    qss.open(QFile::ReadOnly);
    setStyleSheet(qss.readAll());
    qss.close();

}

Widget::~Widget()
{
//    delete ui;
}

void Widget::toggleExpand()
{
    expanded=!expanded;
    if(expanded)
    {
        lw->setVisible(true);
        expandButton->setIcon(QIcon(moreIconPixmap));
    }
    else
    {
        lw->setVisible(false);
        expandButton->setIcon(QIcon(lessIconPixmap));
    }
    emit changeSize(this->sizeHint());
}

void Widget::variableListChanged()
{
    printList();
    emit updateVariableList();
}


void Widget::addVariable()
{
    QPushButton *senderButton = static_cast<QPushButton*>(QObject::sender());
    VariableWidget *vw = new VariableWidget(lw);
    if(senderButton==addNumberButton)
    {
        vw->setNumber();
    }
    else if(senderButton==addVectorButton)
    {
        vw->setVector();
    }

    vwList->append(vw);
    variableList->append(vw->variable);
    QListWidgetItem *item = new QListWidgetItem(lw);

    lw->addItem(item);
    item->setSizeHint(vw->sizeHint());
    lw->setItemWidget(item,vw);

//    connect(vw,SIGNAL(nameChange(QString)),this,SLOT(nameChanged(QString)));
//    connect(vw,SIGNAL(typeChange(int)),this,SLOT(typeChanged(int)));
//    connect(vw,SIGNAL(lengthToggle(bool)),this,SLOT(lengthToggled(bool)));
//    connect(vw,SIGNAL(lengthChange(int)),this,SLOT(lengthChanged(int)));
//    connect(vw,SIGNAL(matchToggle(bool)),this,SLOT(matchToggled(bool)));
//    connect(vw,SIGNAL(matchChange(QString)),this,SLOT(matchChanged(QString)));
//    connect(vw,SIGNAL(repeatChange(int)),this,SLOT(repeatChanged(int)));
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
                    outString.append(vecItem->matchBytes.toHex());
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
                outString.append(item->matchBytes.toHex());
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


//void Widget::nameChanged(QString newName)
//{
//    VariableWidget *vw = static_cast<VariableWidget*>(QObject::sender());
//    int index = vwList->indexOf(vw);
//}

//void Widget::typeChanged(int newType)
//{
//    VariableWidget *vw = static_cast<VariableWidget*>(QObject::sender());
//    int index = vwList->indexOf(vw);
//}


//void Widget::lengthToggled(bool fixed)
//{
//    VariableWidget *vw = static_cast<VariableWidget*>(QObject::sender());
//    int index = vwList->indexOf(vw);
//}

//void Widget::lengthChanged(int newLength)
//{
//    VariableWidget *vw = static_cast<VariableWidget*>(QObject::sender());
//    int index = vwList->indexOf(vw);
//}

//void Widget::matchToggled(bool matched)
//{
//    VariableWidget *vw = static_cast<VariableWidget*>(QObject::sender());
//    int index = vwList->indexOf(vw);
//}

//void Widget::matchChanged(QString newMatch)
//{
//    VariableWidget *vw = static_cast<VariableWidget*>(QObject::sender());
//    int index = vwList->indexOf(vw);
//}

//void Widget::repeatChanged(int newRepeat)
//{
//    VariableWidget *vw = static_cast<VariableWidget*>(QObject::sender());
//    int index = vwList->indexOf(vw);
//}
