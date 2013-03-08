#ifndef WIDGETDRAG_H
#define WIDGETDRAG_H

#include <QWidget>
#include "variablewidget.h"
#include <QList>
#include <QModelIndexList>
#include <QListWidgetItem>
#include "livelistwidget.h"

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
signals:
    void updateVariableList();
private:
    Ui::Widget *ui;
    QList<VariableWidget*> *vwList;
    LiveListWidget *lw;
private slots:
    // Widget handling
    void addVariable();
    void remVariable();
    void resorted(int,int,QListWidgetItem*);
    void itemRemoved(int);
    void itemSize(QSize);

    // Variable data
//    void nameChanged(QString);
//    void typeChanged(int);
//    void lengthToggled(bool);
//    void lengthChanged(int);
//    void matchToggled(bool);
//    void matchChanged(QString);
//    void repeatChanged(int);

    void variableListChanged();
    // Testing operation
    void printList();
};

#endif // WIDGETDRAG_H
