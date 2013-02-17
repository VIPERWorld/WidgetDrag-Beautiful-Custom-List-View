#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H

#include <QListWidget>
#include <QKeyEvent>

class MyListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit MyListWidget(QWidget *parent = 0);
    
signals:
    void itemMoved(int,int,QListWidgetItem*);
    void itemRemoved(int);
public slots:

private:
    QListWidgetItem *temp_item;
    int drag_row;

protected:
   void dropEvent(QDropEvent *event);
   void startDrag(Qt::DropActions supportedActions);
   void keyPressEvent(QKeyEvent *event);

};

#endif // MYLISTWIDGET_H
