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
    
private:
    Ui::Widget *ui;
    QList<VariableWidget*> *vwList;
    MyListWidget *lw;
private slots:
    void nameChanged(QString);
//    void resorted(QModelIndex,int,int,QModelIndex,int,QPrivateSignal);
    void addVariable();
    void remVariable();
    void resorted(int,int,QListWidgetItem*);
    void removed(int);
    void itemSelected(QListWidgetItem*);
    void differentRow(int);
    void itemSize(QSize);
};

#endif // WIDGETDRAG_H
