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
    matchIconPixmap = QPixmap("../WidgetDrag/match_icon.png");

    currentType = BYTTYPE;

    QIcon typeIcon=byteIconPixmap;
    QIcon lengthIcon=fixlenIconPixmap;

    // Title
    title = new QLabel("variable");
    title->setMinimumWidth(80);
    title->setFixedHeight(20);
    typeIndicator = new QPushButton;
    typeIndicator->setIcon(typeIcon);
    typeIndicator->setFixedWidth(20);
    typeIndicator->setFixedHeight(20);
    typeIndicator->setFlat(true);
    lengthIndicator = new QPushButton;
    lengthIndicator->setIcon(lengthIcon);
    lengthIndicator->setFixedWidth(20);
    lengthIndicator->setFixedHeight(20);
    lengthIndicator->setFlat(true);
    matchIndicator = new QPushButton;
    matchIndicator->setFixedWidth(20);
    matchIndicator->setFixedHeight(20);
    matchIndicator->setFlat(true);
    moreButton = new QPushButton("More");
    moreButton->setCheckable(true);
    moreButton->setChecked(true);
    moreButton->setFixedHeight(30);
    delButton = new QPushButton("Delete");
    delButton->setFixedHeight(30);
    titleLayout = new QHBoxLayout;

    titleLayout->addWidget(title);
    titleLayout->addWidget(typeIndicator);
    titleLayout->addWidget(lengthIndicator);
    titleLayout->addWidget(matchIndicator);
    titleLayout->addWidget(moreButton);
    titleLayout->addWidget(delButton);
    //    titleLayout->setGeometry(QRect(0,0,160,20));

    // Name
    nameLabel = new QLabel("Name");
    nameEdit = new QLineEdit("variable");

    // Type
    typeLabel = new QLabel("Type");
    byteButton = new QPushButton("Byte");
    byteButton->setEnabled(false);
    numberButton = new QPushButton("Number");
    vectorButton = new QPushButton("Vector");
    typeLayout = new QHBoxLayout;
    typeLayout->addWidget(byteButton);
    typeLayout->addWidget(numberButton);
    typeLayout->addWidget(vectorButton);
    typeLayout->setSpacing(0);
    typeLayout->setMargin(0);

    commonLayout = new QGridLayout;
    commonLayout->addWidget(nameLabel,0,0);
    commonLayout->addWidget(nameEdit,0,1);
    commonLayout->addWidget(typeLabel,1,0);
    commonLayout->addLayout(typeLayout,1,1);

    // Single variable

    // Length
    lengthLabel = new QLabel("Length");
    lengthCheck = new QCheckBox("Fixed");
    lengthCheck->setChecked(true);
    lengthSpin = new QSpinBox;
    lengthSpin->setValue(1);
    lengthSpin->setMinimumWidth(60);
    lengthLayout = new QHBoxLayout;
    lengthLayout->addStretch(1);
    lengthLayout->addWidget(lengthCheck);
    lengthLayout->addStretch(1);
    lengthLayout->addWidget(lengthSpin);
    lengthLayout->addStretch(1);

    // Match
    matchLabel = new QLabel("Match");
    matchCheck = new QCheckBox;
    matchEdit = new QLineEdit;
    matchLayout = new QHBoxLayout;
    matchLayout->addWidget(matchCheck);
    matchLayout->addWidget(matchEdit);

    singleLayout = new QGridLayout;
    singleLayout->addWidget(lengthLabel,0,0);
    singleLayout->addLayout(lengthLayout,0,1);
    singleLayout->addWidget(matchLabel,1,0);
    singleLayout->addLayout(matchLayout,1,1);

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
    addVectorItemLayout = new QHBoxLayout;
    addVectorItemLayout->addWidget(addVectorByteButton);
    addVectorItemLayout->addWidget(addVectorNumberButton);

    tableWidget = new QTableWidget(1,7);
    tableWidget->setVisible(false);
    QStringList headers;
    headers.append("Name");
    headers.append("Type");
    headers.append("");
    headers.append("Length");
    headers.append("");
    headers.append("Match");
    headers.append("");
    tableWidget->setHorizontalHeaderLabels(headers);
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->setDragDropMode(QAbstractItemView::InternalMove);
    tableWidget->setAcceptDrops(false);
    tableWidget->setColumnWidth(0,80);
    tableWidget->setColumnWidth(1,40);
    tableWidget->setColumnWidth(2,20);
    tableWidget->setColumnWidth(3,60);
    tableWidget->setColumnWidth(4,20);
    tableWidget->setColumnWidth(5,80);
    tableWidget->resizeColumnsToContents();

    QCheckBox *lenCheck = new QCheckBox;

    QTableWidgetItem *newItem0 = new QTableWidgetItem("var1");
    QTableWidgetItem *newItem1 = new QTableWidgetItem;
    QTableWidgetItem *newItem2 = new QTableWidgetItem;
    QTableWidgetItem *newItem3 = new QTableWidgetItem("Spin");
    QTableWidgetItem *newItem4 = new QTableWidgetItem("M");
    QTableWidgetItem *newItem5 = new QTableWidgetItem("LineEdit");

    tableWidget->setItem(0, 0, newItem0);
    newItem1->setIcon(QIcon(byteIconPixmap));
    newItem1->setData(Qt::AlignHCenter,Qt::TextAlignmentRole);
    tableWidget->setItem(0, 1, newItem1);
    tableWidget->setItem(0, 2, newItem2);
    tableWidget->setCellWidget(0,2,lenCheck);
    newItem2->setData(Qt::AlignHCenter,Qt::TextAlignmentRole);
    tableWidget->setItem(0, 3, newItem3);
    tableWidget->setItem(0, 4, newItem4);
    tableWidget->setItem(0, 5, newItem5);

    //tableWidget->setColumnWidth(4,80);
    //tableWidget->setItem(0, 5, newItem6);
    vectorListLayout = new QHBoxLayout;
    vectorListLayout->addWidget(tableWidget);

    vectorLayout = new QGridLayout;
    vectorLayout->addWidget(repeatLabel,0,0);
    vectorLayout->addLayout(repeatLayout,0,1);
    vectorLayout->addWidget(addVectorItemLabel,1,0);
    vectorLayout->addLayout(addVectorItemLayout,1,1);
    vectorLayout->addLayout(vectorListLayout,2,0,2,2,Qt::AlignLeft);
    //    vectorLayout

    // Expanded
    expandedLayout = new QVBoxLayout;
    expandedLayout->addLayout(commonLayout);
    expandedLayout->addLayout(singleLayout);

    // Main
    mainLayout = new QVBoxLayout(this);

    mainLayout->addLayout(titleLayout);
    mainLayout->addLayout(expandedLayout);
    //    mainLayout->addLayout(singleLayout);
    //    mainLayout->setContentsMargins(2,5,10,5);
    this->setLayout(mainLayout);
    this->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
//    this->setMinimumWidth(400);
    connect(nameEdit,SIGNAL(textChanged(QString)),title,SLOT(setText(QString)));
    connect(nameEdit,SIGNAL(textChanged(QString)),this,SIGNAL(nameChange(QString)));
    connect(moreButton,SIGNAL(toggled(bool)),this,SLOT(expanded(bool)));
    connect(delButton,SIGNAL(clicked()),this,SIGNAL(deleteVar()));
    connect(byteButton,SIGNAL(clicked()),this,SLOT(setByte()));
    connect(numberButton,SIGNAL(clicked()),this,SLOT(setNumber()));
    connect(vectorButton,SIGNAL(clicked()),this,SLOT(setVector()));
    connect(lengthCheck,SIGNAL(toggled(bool)),this,SLOT(toggleLength(bool)));
    connect(lengthSpin,SIGNAL(valueChanged(int)),this,SLOT(changeLength(int)));
    connect(matchCheck,SIGNAL(toggled(bool)),this,SLOT(toggleMatch(bool)));
    connect(matchEdit,SIGNAL(textChanged(QString)),this,SLOT(changeMatch(QString)));
    connect(addVectorByteButton,SIGNAL(clicked()),this,SLOT(addVectorByte()));
    connect(tableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(tableCellClicked(int,int)));
}

QString VariableWidget::getName()
{
    return title->text();
}

void VariableWidget::expanded(bool expand)
{
    if(expand)
    {
        mainLayout->addLayout(expandedLayout);
        //        mainLayout->addWidget(check);
    }
    else
    {
        mainLayout->removeItem(expandedLayout);
        //        mainLayout->removeWidget(check);
    }
    //    check->setVisible(expand);

    nameLabel->setVisible(expand);
    nameEdit->setVisible(expand);
    typeLabel->setVisible(expand);
    byteButton->setVisible(expand);
    numberButton->setVisible(expand);
    vectorButton->setVisible(expand);

    emit sizeToggled(this->sizeHint());
}

void VariableWidget::setByte()
{
    QIcon typeIcon=byteIconPixmap;
    typeIndicator->setIcon(typeIcon);
    //    typeIndicator->setText("B");
    byteButton->setEnabled(false);
    numberButton->setEnabled(true);
    vectorButton->setEnabled(true);

    // Handle options' visibility
    if(currentType==VECTYPE)
    {
        // Layout
        expandedLayout->removeItem(vectorLayout);
        expandedLayout->addLayout(singleLayout);

        // Widgets
        repeatLabel->setVisible(false);
        repeatSpin->setVisible(false);
        tableWidget->setVisible(false);
        addVectorItemLabel->setVisible(false);
        addVectorByteButton->setVisible(false);
        addVectorNumberButton->setVisible(false);

        lengthLabel->setVisible(true);
        lengthCheck->setVisible(true);
        lengthSpin->setVisible(true);
        matchLabel->setVisible(true);
        matchCheck->setVisible(true);
        matchEdit->setVisible(true);
    }
    currentType=BYTTYPE;
    emit sizeToggled(this->sizeHint());
}

void VariableWidget::setNumber()
{
    QIcon typeIcon=numberIconPixmap;
    typeIndicator->setIcon(typeIcon);
    //    typeIndicator->setText("N");
    byteButton->setEnabled(true);
    numberButton->setEnabled(false);
    vectorButton->setEnabled(true);

    // Handle options' visibility
    if(currentType==VECTYPE)
    {
        // Layout
        expandedLayout->removeItem(vectorLayout);
        expandedLayout->addLayout(singleLayout);

        // Widgets
        repeatLabel->setVisible(false);
        repeatSpin->setVisible(false);
        tableWidget->setVisible(false);
        addVectorItemLabel->setVisible(false);
        addVectorByteButton->setVisible(false);
        addVectorNumberButton->setVisible(false);

        lengthLabel->setVisible(true);
        lengthCheck->setVisible(true);
        lengthSpin->setVisible(true);
        matchLabel->setVisible(true);
        matchCheck->setVisible(true);
        matchEdit->setVisible(true);
    }
    currentType=NUMTYPE;
    emit sizeToggled(this->sizeHint());
}

void VariableWidget::setVector()
{
    QIcon typeIcon=vectorIconPixmap;
    typeIndicator->setIcon(typeIcon);
    //    typeIndicator->setText("V");
    byteButton->setEnabled(true);
    numberButton->setEnabled(true);
    vectorButton->setEnabled(false);

    // Handle options' visibility
    if(currentType!=VECTYPE)
    {
        // Layout
        expandedLayout->removeItem(singleLayout);
        expandedLayout->addLayout(vectorLayout);

        // Widgets
        repeatLabel->setVisible(true);
        repeatSpin->setVisible(true);
        tableWidget->setVisible(true);
        addVectorItemLabel->setVisible(true);
        addVectorByteButton->setVisible(true);
        addVectorNumberButton->setVisible(true);

        lengthLabel->setVisible(false);
        lengthCheck->setVisible(false);
        lengthSpin->setVisible(false);
        matchLabel->setVisible(false);
        matchCheck->setVisible(false);
        matchEdit->setVisible(false);
    }
    currentType=VECTYPE;
    emit sizeToggled(this->sizeHint());
}

void VariableWidget::toggleLength(bool on)
{
    QIcon lengthIcon;
    if(on)
    {
        lengthIcon=fixlenIconPixmap;
        //        lengthIndicator->setText("L");
    }
    else
    {
        lengthIcon=varlenIconPixmap;
        //        lengthIndicator->clear();
    }
    lengthIndicator->setIcon(lengthIcon);
}

void VariableWidget::changeLength(int newLength)
{

}

void VariableWidget::toggleMatch(bool on)
{
    QIcon matchIcon;
    if(on)
    {
        matchIcon=matchIconPixmap;
        //        lengthIndicator->setText("L");
    }
    else
    {
        matchIcon=QIcon("none");
        //        lengthIndicator->clear();
    }
    matchIndicator->setIcon(matchIcon);
    //    if(on)
    //    {
    //        matchIndicator->setText("M");

    //    }
    //    else
    //    {
    //        matchIndicator->clear();
    //    }
}

void VariableWidget::changeMatch(QString newMatch)
{

}

void VariableWidget::addVectorByte()
{
    int row = tableWidget->rowCount();
    tableWidget->insertRow(row);
    QTableWidgetItem *newItem0 = new QTableWidgetItem("var1");
    QTableWidgetItem *newItem1 = new QTableWidgetItem("Aa");
    QTableWidgetItem *newItem2 = new QTableWidgetItem("L");
    QTableWidgetItem *newItem3 = new QTableWidgetItem("Spin");
    QTableWidgetItem *newItem4 = new QTableWidgetItem("M");
    QTableWidgetItem *newItem5 = new QTableWidgetItem("LineEdit");

    tableWidget->setItem(row, 0, newItem0);
    tableWidget->setItem(row, 1, newItem1);
    tableWidget->setItem(row, 2, newItem2);
    tableWidget->setItem(row, 3, newItem3);
    tableWidget->setItem(row, 4, newItem4);
    tableWidget->setItem(row, 5, newItem5);
}

void VariableWidget::tableCellClicked(int row, int col)
{
    if(col==6)
    {
        tableWidget->removeRow(row);
    }
}
