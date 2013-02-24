#include "variablewidget.h"

VariableWidget::VariableWidget(QWidget *parent) :
    QWidget(parent)
{
    //    this->setFixedWidth(360);
    // Load assets
    byteIconPixmap = QPixmap("../WidgetDrag/byte_icon.png");
    numberIconPixmap = QPixmap("../WidgetDrag/number_icon.png");
    vectorIconPixmap = QPixmap("../WidgetDrag/vector_icon.png");
    varlenIconPixmap = QPixmap("../WidgetDrag/varlen_icon.png");
    fixlenIconPixmap = QPixmap("../WidgetDrag/fixlen_icon.png");
    matchoffIconPixmap = QPixmap("../WidgetDrag/matchoff_icon.png");
    matchonIconPixmap = QPixmap("../WidgetDrag/matchon_icon.png");
    hexoffIconPixmap = QPixmap("../WidgetDrag/hexoff_icon.png");
    hexonIconPixmap = QPixmap("../WidgetDrag/hexon_icon.png");
    cycleIconPixmap = QPixmap("../WidgetDrag/cycle_icon.png");
    addbyteIconPixmap = QPixmap("../WidgetDrag/addbyte_icon.png");
    addnumberIconPixmap = QPixmap("../WidgetDrag/addnumber_icon.png");
    moreIconPixmap = QPixmap("../WidgetDrag/more_icon.png");
    lessIconPixmap = QPixmap("../WidgetDrag/less_icon.png");
    deleteIconPixmap = QPixmap("../WidgetDrag/delete_icon.png");
    cycleIconPixmap = cycleIconPixmap.scaled(20,20,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    currentType = BYTTYPE;
    isExpanded = true;
    fixed=true;
    matched=false;
    hexed=false;

    QIcon typeIcon=byteIconPixmap;
    QIcon lengthIcon=fixlenIconPixmap;
    QIcon matchoffIcon = matchoffIconPixmap;
    QIcon hexoffIcon = hexoffIconPixmap;
    QIcon addbyteIcon = addbyteIconPixmap;
    QIcon addnumberIcon = addnumberIconPixmap;
    QIcon moreIcon = moreIconPixmap;
    QIcon deleteIcon = deleteIconPixmap;

    // Title

    // typeButton & lengthButton
    nameEdit = new QLineEdit("variable");
    nameEdit->setToolTip("Enter the variable name");
    nameEdit->setMinimumWidth(40);
    nameEdit->setFixedHeight(24);
    nameEdit->setFrame(false);
    nameEdit->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    typeButton = new QPushButton;
    typeButton->setToolTip("Toggle between byte, number, and vector type");
    typeButton->setIcon(typeIcon);
    typeButton->setFixedWidth(24);
    typeButton->setFixedHeight(24);
//        typeButton->setFlat(true);

    // Single variable
    lengthButton= new QPushButton;
    lengthButton->setToolTip("Toggle fixed length on or off");
    lengthButton->setIcon(lengthIcon);
    lengthButton->setFixedWidth(24);
    lengthButton->setFixedHeight(24);
    //    lengthButton->setFlat(true);
    lengthSpin = new QSpinBox;
    lengthSpin->setToolTip("Enter a fixed length");
    lengthSpin->setValue(1);
    lengthSpin->setFixedWidth(40);
    lengthSpin->setFixedHeight(24);
    matchButton = new QPushButton;
    matchButton->setToolTip("Toggle match on or off");
    matchButton->setFixedWidth(24);
    matchButton->setFixedHeight(24);
    //    matchButton->setFlat(true);
    matchButton->setIcon(matchoffIcon);
    matchEdit = new QLineEdit;
    matchEdit->setToolTip("Enter the byte array to match");
    //    matchEdit->setFixedWidth(100);
    matchEdit->setFixedHeight(24);
    matchEdit->setFrame(false);
    matchEdit->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    hexButton = new QPushButton;
    hexButton->setToolTip("Toggle between ASCII and hexadecimal display");
    hexButton->setFixedWidth(24);
    hexButton->setFixedHeight(24);
    //    hexButton->setFlat(true);
    hexButton->setIcon(hexoffIcon);

    // Repeat
    repeatLabel = new QLabel;
    repeatLabel->setPixmap(cycleIconPixmap);
    repeatLabel->setFixedSize(24,24);
    repeatLabel->setVisible(false);
    repeatSpin = new QSpinBox;
    repeatSpin->setToolTip("Enter the number of times the vector will be received");
    repeatSpin->setMinimum(1);
    repeatSpin->setValue(5);
    repeatSpin->setVisible(false);
    repeatSpin->setFixedWidth(40);

    addByteButton = new QPushButton;
    addByteButton->setIcon(addbyteIcon);
    addByteButton->setFixedSize(24,24);
    addByteButton->setVisible(false);
    addNumberButton = new QPushButton;
    addNumberButton->setIcon(addnumberIcon);
    addNumberButton->setFixedSize(24,24);
    addNumberButton->setVisible(false);

    // Expand / Delete Buttons
    moreButton = new QPushButton;

    moreButton->setFixedWidth(24);
    moreButton->setFixedHeight(24);
    moreButton->setIcon(moreIcon);
    moreButton->setVisible(false);
    //    moreButton->setFlat(true);
    delButton = new QPushButton;
    delButton->setToolTip("Remove variable");
    delButton->setFixedWidth(24);
    delButton->setFixedHeight(24);
    delButton->setIcon(deleteIcon);
    //    delButton->setFlat(true);

    titleLayout = new QHBoxLayout;
    titleLayout->addWidget(nameEdit);
    titleLayout->addWidget(typeButton);
    titleLayout->addWidget(lengthButton);
    titleLayout->addWidget(repeatLabel);
    titleLayout->addWidget(lengthSpin);
    titleLayout->addWidget(repeatSpin);
    titleLayout->addWidget(addByteButton);
    titleLayout->addWidget(addNumberButton);
    titleLayout->addWidget(matchButton);
    titleLayout->addWidget(matchEdit);
    titleLayout->addWidget(hexButton);
    titleLayout->addWidget(moreButton);
    titleLayout->addWidget(delButton);
    titleLayout->setMargin(0);


    vectorItemList = new MyListWidget(this);
    vectorItemList->setVisible(false);
    vectorItemList->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);

    addVectorByte();

    vectorListLayout = new QHBoxLayout;
    vectorListLayout->addSpacing(10);
    vectorListLayout->addWidget(vectorItemList);

    // Main
    mainLayout = new QVBoxLayout(this);

    mainLayout->addLayout(titleLayout);
    this->setLayout(mainLayout);
    this->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    connect(delButton,SIGNAL(clicked()),this,SIGNAL(deleteVar()));
    connect(typeButton,SIGNAL(clicked()),this,SLOT(toggleType()));
    connect(lengthButton,SIGNAL(clicked()),this,SLOT(toggleLength()));
    connect(lengthSpin,SIGNAL(valueChanged(int)),this,SLOT(changeLength(int)));
    connect(matchButton,SIGNAL(clicked()),this,SLOT(toggleMatch()));
    connect(hexButton,SIGNAL(clicked()),this,SLOT(toggleHex()));
    connect(matchEdit,SIGNAL(textChanged(QString)),this,SLOT(changeMatch(QString)));
    connect(addByteButton,SIGNAL(clicked()),this,SLOT(addVectorByte()));
    connect(addNumberButton,SIGNAL(clicked()),this,SLOT(addVectorNumber()));
    connect(moreButton,SIGNAL(clicked()),this,SLOT(toggleExpand()));

    QFile qss("../WidgetDrag/variablewidget.css");
    qss.open(QFile::ReadOnly);
    setStyleSheet(qss.readAll());
    qss.close();

    emit sizeToggled(this->sizeHint());
}

QString VariableWidget::getName()
{
    return nameEdit->text();
}

void VariableWidget::toggleType()
{
    currentType++;
    switch(currentType)
    {
    case 1:
        typeButton->setIcon(QIcon(numberIconPixmap));
        setNumber();
        break;
    case 2:
        typeButton->setIcon(QIcon(vectorIconPixmap));
        moreButton->setIcon(QIcon(moreIconPixmap));
        isExpanded=true;
        setVector();
        break;
    default:
        currentType=0;
        setByte();
        typeButton->setIcon(QIcon(byteIconPixmap));
        break;
    }
}

void VariableWidget::toggleExpand(bool expand)
{

    if(expand)
    {
        vectorItemList->setVisible(true);
        mainLayout->addLayout(vectorListLayout);
        moreButton->setIcon(QIcon(moreIconPixmap));
    }
    else
    {
        vectorItemList->setVisible(false);
        mainLayout->removeItem(vectorListLayout);
        moreButton->setIcon(QIcon(lessIconPixmap));
    }

    emit sizeToggled(this->sizeHint());
}

void VariableWidget::toggleExpand()
{
    isExpanded = !isExpanded;
    toggleExpand(isExpanded);
}

void VariableWidget::setByte()
{
    QIcon typeIcon=byteIconPixmap;
    typeButton->setIcon(typeIcon);

    mainLayout->removeItem(vectorListLayout);

    repeatLabel->setVisible(false);
    repeatSpin->setVisible(false);
    addByteButton->setVisible(false);
    addNumberButton->setVisible(false);
    moreButton->setVisible(false);
    vectorItemList->setVisible(false);


    lengthButton->setVisible(true);
    lengthButton->setEnabled(true);
    lengthSpin->setVisible(true);
    lengthSpin->setEnabled(true);

    matchButton->setVisible(true);
    matchButton->setEnabled(true);
    matchEdit->setVisible(true);
    matchEdit->setEnabled(true);
    hexButton->setVisible(true);
    hexButton->setEnabled(true);



    currentType=BYTTYPE;
    emit sizeToggled(this->sizeHint());
}

void VariableWidget::setNumber()
{
    QIcon typeIcon=numberIconPixmap;
    typeButton->setIcon(typeIcon);

    // Widgets
    mainLayout->removeItem(vectorListLayout);

    repeatLabel->setVisible(false);
    repeatSpin->setVisible(false);
    addByteButton->setVisible(false);
    addNumberButton->setVisible(false);
    moreButton->setVisible(false);
    vectorItemList->setVisible(false);

    lengthButton->setVisible(true);
    lengthButton->setEnabled(true);
    lengthSpin->setVisible(true);
    lengthButton->setEnabled(true);

    matchButton->setVisible(true);
    matchButton->setEnabled(false);
    matchEdit->setVisible(true);
    matchEdit->setEnabled(false);
    hexButton->setVisible(true);
    hexButton->setEnabled(false);



    currentType=NUMTYPE;
    emit sizeToggled(this->sizeHint());

}

void VariableWidget::setVector()
{
    QIcon typeIcon=vectorIconPixmap;
    typeButton->setIcon(typeIcon);

    lengthButton->setVisible(false);
    lengthSpin->setVisible(false);

    matchButton->setVisible(false);
    matchEdit->setVisible(false);
    hexButton->setVisible(false);


    repeatLabel->setVisible(true);
    repeatSpin->setVisible(true);
    addByteButton->setVisible(true);
    addNumberButton->setVisible(true);
    moreButton->setVisible(true);
    vectorItemList->setVisible(true);
    mainLayout->addLayout(vectorListLayout);

    currentType=VECTYPE;
    emit sizeToggled(this->sizeHint());
}

void VariableWidget::toggleLength()
{
    QIcon lengthIcon;
    fixed =!fixed;
    if(fixed)
    {
        lengthIcon=fixlenIconPixmap;
    }
    else
    {
        lengthIcon=varlenIconPixmap;
    }
    lengthButton->setIcon(lengthIcon);
}

void VariableWidget::changeLength(int newLength)
{

}

void VariableWidget::toggleMatch()
{
    QIcon matchIcon;
    matched=!matched;

    if(matched)
    {
        matchIcon=matchonIconPixmap;
    }
    else
    {
        matchIcon=matchoffIconPixmap;
    }
    matchButton->setIcon(matchIcon);

}

void VariableWidget::toggleHex()
{
    QIcon hexIcon;
    hexed=!hexed;

    if(hexed)
    {
        hexIcon=hexonIconPixmap;
    }
    else
    {
        hexIcon=hexoffIconPixmap;
    }
    hexButton->setIcon(hexIcon);

}

void VariableWidget::changeMatch(QString newMatch)
{

}

void VariableWidget::addVectorByte()
{
    QListWidgetItem *item = new QListWidgetItem;
    VectorItemWidget *iw = new VectorItemWidget(this);
    vectorItemList->addItem(item);
    item->setSizeHint(iw->sizeHint());
    vectorItemList->setItemWidget(item,iw);
    connect(iw,SIGNAL(deleteVar()),this,SLOT(vectorItemRemove()));
}

void VariableWidget::addVectorNumber()
{
    QListWidgetItem *item = new QListWidgetItem;
    VectorItemWidget *iw = new VectorItemWidget(this);
    vectorItemList->addItem(item);
    item->setSizeHint(iw->sizeHint());
    vectorItemList->setItemWidget(item,iw);
    connect(iw,SIGNAL(deleteVar()),this,SLOT(vectorItemRemove()));
}

void VariableWidget::tableCellClicked(int row, int col)
{
}

void VariableWidget::vectorItemLengthToggled(bool fixed)
{
}

void VariableWidget::vectorItemLengthChanged(int newLength)
{

}

void VariableWidget::vectorItemMatchToggled(bool matched)
{

}

void VariableWidget::vectorItemMatchChanged(QString newMatch)
{
}

void VariableWidget::vectorItemMoveUp()
{

}

void VariableWidget::vectorItemMoveDown()
{

}

void VariableWidget::vectorItemRemove()
{
    VectorItemWidget *op_sender = static_cast<VectorItemWidget*>(QObject::sender());
    qDebug() << "signal caught";
    int row;
    for(quint8 i =0;i<vectorItemList->count();i++)
    {
        QListWidgetItem *item = vectorItemList->item(i);
        VectorItemWidget *op_match = static_cast<VectorItemWidget*>(vectorItemList->itemWidget(item));
        if(op_sender==op_match)
        {
            // Row identified
            qDebug() << "Vector item # " << i << "has requested to be removed";
            row=i;

        }
    }
    vectorItemList->removeItemWidget(vectorItemList->item(row));
    vectorItemList->takeItem(row);


}
