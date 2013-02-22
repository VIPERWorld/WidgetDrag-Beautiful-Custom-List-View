#ifndef VARIABLEWIDGET_H
#define VARIABLEWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QSpinBox>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include "mylistwidget.h"
#include "vectoritemwidget.h"

#include <parserengine.h>
#include <QDebug>
#include "qcenteredcell.h"
#include "checkspinitem.h"
#include "checkedititem.h"
#include "vectoropsitem.h"

#define BYTTYPE 0
#define NUMTYPE 1
#define VECTYPE 2

class VariableWidget : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout *mainLayout;

    // Title
    QLineEdit *nameEdit;
    QPushButton *typeButton;
    QPushButton *lengthButton;
    QPushButton *matchButton;
    QPushButton *moreButton;
    QPushButton *delButton;
    QHBoxLayout *titleLayout;

    QSpinBox *lengthSpin;
    QLineEdit *matchEdit;
    QPushButton *hexButton;

    // Vector variable
    QLabel *repeatLabel;
//    QIcon *iconLabel;
    QSpinBox *repeatSpin;

    QPushButton *addByteButton;
    QPushButton *addNumberButton;

//    QHBoxLayout *repeatLayout;

//    QLabel *addVectorItemLabel;
//    QPushButton *addVectorByteButton;
//    QPushButton *addVectorNumberButton;

    MyListWidget *vectorItemList;

    QHBoxLayout *vectorListLayout;
    QGridLayout *vectorLayout;

    QVBoxLayout *expandedLayout;

    // Assets
    QPixmap byteIconPixmap;
    QPixmap numberIconPixmap;
    QPixmap vectorIconPixmap;
    QPixmap varlenIconPixmap;
    QPixmap fixlenIconPixmap;
    QPixmap matchoffIconPixmap;
    QPixmap matchonIconPixmap;
    QPixmap hexonIconPixmap;
    QPixmap hexoffIconPixmap;
    QPixmap cycleIconPixmap;
    QPixmap addbyteIconPixmap;
    QPixmap addnumberIconPixmap;
    QPixmap moreIconPixmap;
    QPixmap lessIconPixmap;
    QPixmap deleteIconPixmap;

    int currentType;
    bool matched;
    bool fixed;
    bool hexed;
    bool isExpanded;


public:
    explicit VariableWidget(QWidget *parent = 0);
    QString getName(void);

signals:
    void nameChange(QString);
    void sizeToggled(QSize);
    void deleteVar();
public slots:
    void toggleExpand(bool);
    void toggleExpand();
    void setByte();
    void setNumber();
    void setVector();
    void toggleType();
    void toggleLength();
    void changeLength(int);
    void toggleMatch();
    void changeMatch(QString);
    void toggleHex();
    void addVectorItem(void);
    void addVectorItem(int);
    void tableCellClicked(int,int);
    void vectorItemLengthToggled(bool);
    void vectorItemLengthChanged(int);
    void vectorItemMatchToggled(bool);
    void vectorItemMatchChanged(QString);
    void vectorItemMoveUp();
    void vectorItemMoveDown();
    void vectorItemRemove();
};

#endif // VARIABLEWIDGET_H
