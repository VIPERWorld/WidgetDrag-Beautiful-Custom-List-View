#include "variablewidget.h"

VariableWidget::VariableWidget(QWidget *parent) :
    QWidget(parent)
{
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
    moreIconPixmap = QPixmap("../WidgetDrag/more_icon.png");
    lessIconPixmap = QPixmap("../WidgetDrag/less_icon.png");
    deleteIconPixmap = QPixmap("../WidgetDrag/delete_icon.png");

    currentType = BYTTYPE;
    isExpanded = true;
    fixed=true;
    matched=false;
    hexed=false;

    QIcon typeIcon=byteIconPixmap;
    QIcon lengthIcon=fixlenIconPixmap;
    QIcon matchoffIcon = matchoffIconPixmap;
    QIcon hexoffIcon = hexoffIconPixmap;
    QIcon lessIcon = lessIconPixmap;
    QIcon deleteIcon = deleteIconPixmap;

    // Title

    // typeButton & lengthButton
    nameEdit = new QLineEdit("variable");
    nameEdit->setToolTip("Enter the variable name");
    nameEdit->setMinimumWidth(80);
    nameEdit->setFixedHeight(20);
    typeButton = new QPushButton;
    typeButton->setToolTip("Toggle between byte, number, and vector type");
    typeButton->setIcon(typeIcon);
    typeButton->setFixedWidth(24);
    typeButton->setFixedHeight(24);
    typeButton->setFlat(true);

    // Single variable
    lengthButton= new QPushButton;
    lengthButton->setToolTip("Toggle fixed length on or off");
    lengthButton->setIcon(lengthIcon);
    lengthButton->setFixedWidth(24);
    lengthButton->setFixedHeight(24);
    lengthButton->setFlat(true);
    lengthSpin = new QSpinBox;
    lengthSpin->setToolTip("Enter a fixed length");
    lengthSpin->setValue(1);
    lengthSpin->setFixedWidth(40);
    matchButton = new QPushButton;
    matchButton->setToolTip("Toggle match on or off");
    matchButton->setFixedWidth(24);
    matchButton->setFixedHeight(24);
    matchButton->setFlat(true);
    matchButton->setIcon(matchoffIcon);
    matchEdit = new QLineEdit;
    matchEdit->setToolTip("Enter the byte array to match");
    matchEdit->setFixedWidth(100);
    hexButton = new QPushButton;
    hexButton->setToolTip("Toggle between ASCII and hexadecimal display");
    hexButton->setFixedWidth(24);
    hexButton->setFixedHeight(24);
    hexButton->setFlat(true);
    hexButton->setIcon(hexoffIcon);


    // Expand / Delete Buttons
    moreButton = new QPushButton;
    moreButton->setFixedWidth(24);
    moreButton->setFixedHeight(24);
    moreButton->setIcon(lessIcon);
    moreButton->setFlat(true);
    delButton = new QPushButton;
    delButton->setFixedWidth(24);
    delButton->setFixedHeight(24);
    delButton->setIcon(deleteIcon);
    delButton->setFlat(true);
    titleLayout = new QHBoxLayout;

    titleLayout->addWidget(nameEdit);
    titleLayout->addWidget(typeButton);
    titleLayout->addWidget(lengthButton);
    titleLayout->addWidget(lengthSpin);
    titleLayout->addWidget(matchButton);
    titleLayout->addWidget(matchEdit);
    titleLayout->addWidget(hexButton);
    titleLayout->addWidget(moreButton);
    titleLayout->addWidget(delButton);
    titleLayout->setMargin(0);

    // Vector variable

    // Repeat
    repeatLabel = new QLabel("Repetitions");
    repeatSpin = new QSpinBox;
    repeatSpin->setValue(5);
    repeatLabel->setVisible(false);
    repeatSpin->setVisible(false);
    repeatSpin->setMinimumWidth(80);
    repeatLayout = new QHBoxLayout;
    repeatLayout->addStretch(1);
    repeatLayout->addWidget(repeatSpin);
    repeatLayout->addStretch(1);

    // Vector items

    addVectorItemLabel = new QLabel("Add item");
    addVectorByteButton = new QPushButton("Byte");
    addVectorNumberButton = new QPushButton("Number");

    repeatLayout->addWidget(addVectorItemLabel);
    repeatLayout->addWidget(addVectorByteButton);
    repeatLayout->addWidget(addVectorNumberButton);

    vectorItemList = new MyListWidget(this);
    vectorItemList->setVisible(false);
    vectorItemList->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);
    QListWidgetItem *item = new QListWidgetItem;
    VectorItemWidget *iw = new VectorItemWidget(this);
    vectorItemList->addItem(item);
    item->setSizeHint(iw->sizeHint());
    vectorItemList->setItemWidget(item,iw);

    addVectorItem(BYTTYPE);

    vectorListLayout = new QHBoxLayout;
    vectorListLayout->addWidget(vectorItemList);

    vectorLayout = new QGridLayout;
    vectorLayout->addWidget(repeatLabel,0,0);
    vectorLayout->addLayout(repeatLayout,0,1);
    vectorLayout->addLayout(vectorListLayout,2,0,1,2,Qt::AlignHCenter);


    // Expanded
    expandedLayout = new QVBoxLayout;

    // Main
    mainLayout = new QVBoxLayout(this);

    mainLayout->addLayout(titleLayout);
    mainLayout->addLayout(expandedLayout);
    this->setLayout(mainLayout);
    this->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    connect(moreButton,SIGNAL(clicked()),this,SLOT(toggleExpand()));
    connect(delButton,SIGNAL(clicked()),this,SIGNAL(deleteVar()));
    connect(typeButton,SIGNAL(clicked()),this,SLOT(toggleType()));
    connect(lengthButton,SIGNAL(clicked()),this,SLOT(toggleLength()));
    connect(lengthSpin,SIGNAL(valueChanged(int)),this,SLOT(changeLength(int)));
    connect(matchButton,SIGNAL(clicked()),this,SLOT(toggleMatch()));
    connect(hexButton,SIGNAL(clicked()),this,SLOT(toggleHex()));
    connect(matchEdit,SIGNAL(textChanged(QString)),this,SLOT(changeMatch(QString)));
    connect(addVectorByteButton,SIGNAL(clicked()),this,SLOT(addVectorItem()));
    connect(addVectorNumberButton,SIGNAL(clicked()),this,SLOT(addVectorItem()));

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
        break;
    case 2:
        typeButton->setIcon(QIcon(vectorIconPixmap));
        break;
    default:
        currentType=0;
        typeButton->setIcon(QIcon(byteIconPixmap));
        break;
    }
}

void VariableWidget::toggleExpand(bool expand)
{
    if(expand)
    {
        mainLayout->addLayout(expandedLayout);
        moreButton->setIcon(QIcon(lessIconPixmap));
    }
    else
    {
        mainLayout->removeItem(expandedLayout);
        moreButton->setIcon(QIcon(moreIconPixmap));
    }

    emit sizeToggled(this->sizeHint());
}

void VariableWidget::toggleExpand()
{
    if(isExpanded)
    {
        toggleExpand(false);
        isExpanded=false;
    }
    else
    {
        toggleExpand(true);
        isExpanded=true;

    }
}

void VariableWidget::setByte()
{
    QIcon typeIcon=byteIconPixmap;
    typeButton->setIcon(typeIcon);

    lengthButton->setEnabled(true);
    matchButton->setEnabled(true);

    matchEdit->setVisible(true);
    // Handle options' visibility
    if(currentType==VECTYPE)
    {
        // Layout
        expandedLayout->removeItem(vectorLayout);

        // Widgets
        repeatLabel->setVisible(false);
        repeatSpin->setVisible(false);
        vectorItemList->setVisible(false);
        addVectorItemLabel->setVisible(false);
        addVectorByteButton->setVisible(false);
        addVectorNumberButton->setVisible(false);

        lengthSpin->setVisible(true);

    }
    currentType=BYTTYPE;
    emit sizeToggled(this->sizeHint());
}

void VariableWidget::setNumber()
{
    QIcon typeIcon=numberIconPixmap;
    typeButton->setIcon(typeIcon);

    // Widgets
    lengthButton->setEnabled(true);
    matchButton->setEnabled(false);
    matchEdit->setVisible(false);

    // Handle options' visibility
    if(currentType==VECTYPE)
    {
        // Layout
        expandedLayout->removeItem(vectorLayout);

        repeatLabel->setVisible(false);
        repeatSpin->setVisible(false);
        vectorItemList->setVisible(false);
        addVectorItemLabel->setVisible(false);
        addVectorByteButton->setVisible(false);
        addVectorNumberButton->setVisible(false);

       lengthSpin->setVisible(true);

    }
    currentType=NUMTYPE;

    emit sizeToggled(this->sizeHint());

}

void VariableWidget::setVector()
{
    QIcon typeIcon=vectorIconPixmap;
    typeButton->setIcon(typeIcon);

    lengthButton->setEnabled(false);
    matchButton->setEnabled(false);


    // Handle options' visibility
    if(currentType!=VECTYPE)
    {
        // Layout
        expandedLayout->addLayout(vectorLayout);

        // Widgets
        repeatLabel->setVisible(true);
        repeatSpin->setVisible(true);
        vectorItemList->setVisible(true);
        addVectorItemLabel->setVisible(true);
        addVectorByteButton->setVisible(true);
        addVectorNumberButton->setVisible(true);

        lengthSpin->setVisible(false);
        matchEdit->setVisible(false);

    }
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

void VariableWidget::addVectorItem(int varType)
{
}

void VariableWidget::addVectorItem()
{
    QPushButton *btn = static_cast<QPushButton*>(QObject::sender());
    if(btn==addVectorByteButton)
    {

        addVectorItem(BYTTYPE);
    }
    else
    {
        addVectorItem(NUMTYPE);
    }
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

}
