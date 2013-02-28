#ifndef WIDGETDRAG_H
#define WIDGETDRAG_H

#include <QWidget>
#include "variablewidget.h"
#include <QList>
#include <QModelIndexList>
#include <QListWidgetItem>
#include "mylistwidget.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QList<ComplexVariable*> *variableList;

private:
    Ui::Widget *ui;
    QList<VariableWidget*> *vwList;
    MyListWidget *lw;
private slots:
    // Widget handling
    void addVariable();
    void remVariable();
    void resorted(int,int,QListWidgetItem*);
    void itemRemoved(int);
    void itemSelected(QListWidgetItem*);
    void differentRow(int);
    void itemSize(QSize);

    // Variable data
    void nameChanged(QString);
    void typeChanged(int);
    void lengthToggled(bool);
    void lengthChanged(int);
    void matchToggled(bool);
    void matchChanged(QString);
    void repeatChanged(int);

    // Testing operation
    void printList();
};

#endif // WIDGETDRAG_H
