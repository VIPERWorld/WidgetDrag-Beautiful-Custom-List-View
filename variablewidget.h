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

#include <parserengine.h>
#include <QDebug>
#include "qcenteredcell.h"
#include "checkspinitem.h"
#include "checkedititem.h"

#define BYTTYPE 0
#define NUMTYPE 1
#define VECTYPE 2

class VariableWidget : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout *mainLayout;

    // Title
    QLabel *title;
    QPushButton *typeIndicator;
    QPushButton *lengthIndicator;
    QPushButton *matchIndicator;
    QPushButton *moreButton;
    QPushButton *delButton;
    QHBoxLayout *titleLayout;

    // Name
    QLabel *nameLabel;
    QLineEdit *nameEdit;

    // Type
    QLabel *typeLabel;
    QPushButton *byteButton;
    QPushButton *numberButton;
    QPushButton *vectorButton;
    QHBoxLayout *typeLayout;

    // Common layout
    QGridLayout *commonLayout;

    // Single variable
    QLabel *lengthLabel;
    QCheckBox *lengthCheck;
    QSpinBox *lengthSpin;
    QHBoxLayout *lengthLayout;
    QLabel *matchLabel;
    QCheckBox *matchCheck;
    QLineEdit *matchEdit;
    QHBoxLayout *matchLayout;
    QGridLayout *singleLayout;

// Vector variable
    QLabel *repeatLabel;
    QSpinBox *repeatSpin;
    QHBoxLayout *repeatLayout;

    QLabel *addVectorItemLabel;
    QPushButton *addVectorByteButton;
    QPushButton *addVectorNumberButton;
    QHBoxLayout *addVectorItemLayout;

    QTableWidget *tableWidget;
    QHBoxLayout *vectorListLayout;
    QGridLayout *vectorLayout;

    QVBoxLayout *expandedLayout;

    // Assets
    QPixmap byteIconPixmap;
    QPixmap numberIconPixmap;
    QPixmap vectorIconPixmap;
    QPixmap varlenIconPixmap;
    QPixmap fixlenIconPixmap;
    QPixmap matchIconPixmap;

    int currentType;

public:
    explicit VariableWidget(QWidget *parent = 0);
    QString getName(void);

signals:
    void nameChange(QString);
    void sizeToggled(QSize);
    void deleteVar();
public slots:
    void expanded(bool);
    void setByte();
    void setNumber();
    void setVector();
    void toggleLength(bool);
    void changeLength(int);
    void toggleMatch(bool);
    void changeMatch(QString);
    void addVectorItem(void);
    void addVectorItem(int);
    void tableCellClicked(int,int);
};

#endif // VARIABLEWIDGET_H
