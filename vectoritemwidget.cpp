#include "vectoritemwidget.h"

VectorItemWidget::VectorItemWidget(QWidget *parent) :
    QWidget(parent)
{
    currentType = BYTTYPE;
    fixed=true;
    matched=false;
    hexed=false;

    setupUi();

    variable = new BaseVariable;
    variable->name = "variable";
    variable->type = BYTTYPE;
    variable->fixed=true;
    variable->match=false;
    variable->length=1;
    variable->matchBytes.clear();
}

void VectorItemWidget::changeName(QString newName)
{
    variable->name = newName;
    emit variableChanged();
    emit nameChange(newName);
}

void VectorItemWidget::toggleType()
{
    switch(currentType)
    {
    case BYTTYPE:

        setNumber();
        break;
    default:
        setByte();
        break;
    }
emit variableChanged();
    emit typeChange(currentType);
}

void VectorItemWidget::setByte()
{
    typeButton->setIcon(QIcon(byteIconPixmap));

    matchButton->setEnabled(true);
    matchEdit->setEnabled(true);
    hexButton->setEnabled(true);

    currentType=BYTTYPE;
    variable->type=currentType;
    emit sizeToggled(this->sizeHint());
}

void VectorItemWidget::setNumber()
{
    typeButton->setIcon(QIcon(numberIconPixmap));

    // Widgets
    matchButton->setEnabled(false);
    matchEdit->setEnabled(false);
    hexButton->setEnabled(false);

    // Handle options' visibility
    currentType=NUMTYPE;
    variable->type=currentType;
    emit sizeToggled(this->sizeHint());
}

void VectorItemWidget::toggleLength()
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
    variable->fixed=fixed;
    emit variableChanged();
    emit lengthToggle(fixed);
}

void VectorItemWidget::changeLength(int newLength)
{
    variable->length = newLength;
    emit variableChanged();
    emit lengthChange(newLength);
}

void VectorItemWidget::toggleMatch()
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
    variable->match = matched;
    emit variableChanged();
    emit matchToggle(matched);
}

void VectorItemWidget::toggleHex()
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

void VectorItemWidget::changeMatch(QString newMatch)
{
    variable->matchBytes = newMatch;
    emit variableChanged();
    emit matchChange(newMatch);
}

void VectorItemWidget::setupUi()
{
    // Load assets
    byteIconPixmap = QPixmap("../WidgetDrag/byte_icon.png");
    numberIconPixmap = QPixmap("../WidgetDrag/number_icon.png");
    varlenIconPixmap = QPixmap("../WidgetDrag/varlen_icon.png");
    fixlenIconPixmap = QPixmap("../WidgetDrag/fixlen_icon.png");
    matchoffIconPixmap = QPixmap("../WidgetDrag/matchoff_icon.png");
    matchonIconPixmap = QPixmap("../WidgetDrag/matchon_icon.png");
    hexoffIconPixmap = QPixmap("../WidgetDrag/hexoff_icon.png");
    hexonIconPixmap = QPixmap("../WidgetDrag/hexon_icon.png");
    deleteIconPixmap = QPixmap("../WidgetDrag/delete_icon.png");
    QIcon typeIcon=byteIconPixmap;
    QIcon lengthIcon=fixlenIconPixmap;
    QIcon matchoffIcon = matchoffIconPixmap;
    QIcon hexoffIcon = hexoffIconPixmap;
    QIcon deleteIcon = deleteIconPixmap;

    // Title

    // typeButton & lengthButton
    nameEdit = new QLineEdit("variable");
    nameEdit->setToolTip("Enter the variable name");
    nameEdit->setMinimumWidth(60);
    nameEdit->setFixedHeight(24);
    nameEdit->setFrame(false);
    typeButton = new QPushButton;
    typeButton->setToolTip("Toggle between byte, number, and vector type");
    typeButton->setIcon(typeIcon);
    typeButton->setFixedWidth(24);
    typeButton->setFixedHeight(24);

    // Single variable
    lengthButton= new QPushButton;
    lengthButton->setToolTip("Toggle fixed length on or off");
    lengthButton->setIcon(lengthIcon);
    lengthButton->setFixedWidth(24);
    lengthButton->setFixedHeight(24);
    lengthSpin = new QSpinBox;
    lengthSpin->setToolTip("Enter a fixed length");
    lengthSpin->setValue(1);
    lengthSpin->setMinimum(1);
    lengthSpin->setFixedWidth(40);
    lengthSpin->setFixedHeight(24);
    matchButton = new QPushButton;
    matchButton->setToolTip("Toggle match on or off");
    matchButton->setFixedWidth(24);
    matchButton->setFixedHeight(24);
    matchButton->setIcon(matchoffIcon);
    matchEdit = new QLineEdit;
    matchEdit->setToolTip("Enter the byte array to match");
    matchEdit->setFixedWidth(100);
    matchEdit->setFixedHeight(24);
    matchEdit->setFrame(false);
    hexButton = new QPushButton;
    hexButton->setToolTip("Toggle between ASCII and hexadecimal display");
    hexButton->setFixedWidth(24);
    hexButton->setFixedHeight(24);
    hexButton->setIcon(hexoffIcon);

    delButton = new QPushButton;
    delButton->setFixedWidth(24);
    delButton->setFixedHeight(24);
    delButton->setIcon(deleteIcon);

    titleLayout = new QHBoxLayout;
    titleLayout->addWidget(nameEdit);
    titleLayout->addWidget(typeButton);
    titleLayout->addWidget(lengthButton);
    titleLayout->addWidget(lengthSpin);
    titleLayout->addWidget(matchButton);
    titleLayout->addWidget(matchEdit);
    titleLayout->addWidget(hexButton);
    titleLayout->addWidget(delButton);
    titleLayout->setMargin(0);

    // Main
    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(titleLayout);
    this->setLayout(mainLayout);
    this->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    connect(delButton,SIGNAL(clicked()),this,SIGNAL(deleteVar()));
    connect(nameEdit,SIGNAL(textChanged(QString)),this,SLOT(changeName(QString)));
    connect(typeButton,SIGNAL(clicked()),this,SLOT(toggleType()));
    connect(lengthButton,SIGNAL(clicked()),this,SLOT(toggleLength()));
    connect(lengthSpin,SIGNAL(valueChanged(int)),this,SLOT(changeLength(int)));
    connect(matchButton,SIGNAL(clicked()),this,SLOT(toggleMatch()));
    connect(hexButton,SIGNAL(clicked()),this,SLOT(toggleHex()));
    connect(matchEdit,SIGNAL(textChanged(QString)),this,SLOT(changeMatch(QString)));
    connect(delButton,SIGNAL(clicked()),this,SIGNAL(deleteVar()));
    emit sizeToggled(this->sizeHint());
}
