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
#include <QDebug>
#include "mylistwidget.h"
#include "vectoritemwidget.h"
#include "parserengine.h"

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
    QSpinBox *repeatSpin;

    QPushButton *addByteButton;
    QPushButton *addNumberButton;

    MyListWidget *vectorItemList;
    QHBoxLayout *vectorListLayout;

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

    QList<VectorItemWidget*> *itemList;

    void setupUI();

public:
    explicit VariableWidget(QWidget *parent = 0);
    ComplexVariable *variable;

signals:
    void nameChange(QString);
    void typeChange(int);
    void lengthToggle(bool);
    void lengthChange(int);
    void matchToggle(bool);
    void matchChange(QString);
    void repeatChange(int);
    void vectorChanged();
//    void propertyChange();

    void sizeToggled(QSize);
    void deleteVar();
public slots:
    void toggleExpand(bool);
    void toggleExpand();
    void nameChanged(QString);
    void setByte();
    void setNumber();
    void setVector();
    void toggleType();
    void toggleLength();
    void changeLength(int);
    void toggleMatch();
    void changeMatch(QString);
    void toggleHex();
    void changeRepeat(int);
    void vectorItemNameChanged(QString);
    void vectorItemTypeChanged(int);
    void vectorItemLengthToggled(bool);
    void vectorItemLengthChanged(int);
    void vectorItemMatchToggled(bool);
    void vectorItemMatchChanged(QString);
    void vectorItemResorted(int,int,QListWidgetItem*);
    void vectorItemRemoved();
    void addVectorByte(void);
    void addVectorNumber(void);
};

#endif // VARIABLEWIDGET_H
