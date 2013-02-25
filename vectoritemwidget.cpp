#include "vectoritemwidget.h"

VectorItemWidget::VectorItemWidget(QWidget *parent) :
    QWidget(parent)
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

    currentType = BYTTYPE;
    fixed=true;
    matched=false;
    hexed=false;

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
    //    typeButton->setFlat(true);

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
    matchEdit->setFixedWidth(100);
     matchEdit->setFixedHeight(24);
    matchEdit->setFrame(false);
    hexButton = new QPushButton;
    hexButton->setToolTip("Toggle between ASCII and hexadecimal display");
    hexButton->setFixedWidth(24);
    hexButton->setFixedHeight(24);
    //    hexButton->setFlat(true);
    hexButton->setIcon(hexoffIcon);

    delButton = new QPushButton;
    delButton->setFixedWidth(24);
    delButton->setFixedHeight(24);
    delButton->setIcon(deleteIcon);
    //    delButton->setFlat(true);

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
    connect(typeButton,SIGNAL(clicked()),this,SLOT(toggleType()));
    connect(lengthButton,SIGNAL(clicked()),this,SLOT(toggleLength()));
    connect(lengthSpin,SIGNAL(valueChanged(int)),this,SLOT(changeLength(int)));
    connect(matchButton,SIGNAL(clicked()),this,SLOT(toggleMatch()));
    connect(hexButton,SIGNAL(clicked()),this,SLOT(toggleHex()));
    connect(matchEdit,SIGNAL(textChanged(QString)),this,SLOT(changeMatch(QString)));
    connect(delButton,SIGNAL(clicked()),this,SIGNAL(deleteVar()));

    emit sizeToggled(this->sizeHint());
}

QString VectorItemWidget::getName()
{
    return nameEdit->text();
}

void VectorItemWidget::toggleType()
{
    currentType++;
    switch(currentType)
    {
    case 1:
        typeButton->setIcon(QIcon(numberIconPixmap));
        setNumber();
        break;
    default:
        currentType=0;
        setByte();
        typeButton->setIcon(QIcon(byteIconPixmap));
        break;
    }
}

void VectorItemWidget::setByte()
{
    QIcon typeIcon=byteIconPixmap;
    typeButton->setIcon(typeIcon);

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

void VectorItemWidget::setNumber()
{
    QIcon typeIcon=numberIconPixmap;
    typeButton->setIcon(typeIcon);

    // Widgets
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

    // Handle options' visibility
    currentType=NUMTYPE;

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
}

void VectorItemWidget::changeLength(int newLength)
{

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

}


