#include "mylistwidget.h"

MyListWidget::MyListWidget(QWidget *parent) :
    QListWidget(parent)
{
    setAcceptDrops(true);
    setDragEnabled(true);
    setDragDropMode(QAbstractItemView::InternalMove);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    QPalette pal = this->palette();
    pal.setColor(QPalette::Base,QColor("black"));

    this->setPalette(pal);
    setStyleSheet("QListView::item:selected {background-color: rgb(20,20,20); border-style: solid; border-color: rgb(0,0,0);}"\
                  "QListView::item:hover { background-color: rgb(50,50,50);}");
}

void MyListWidget::dropEvent(QDropEvent *event)
{
    QListWidget::dropEvent(event);
    emit itemMoved(drag_row,this->row(temp_item),temp_item);
}

void MyListWidget::startDrag(Qt::DropActions supportedActions)
{
    temp_item  = currentItem();
    drag_row= this->row(temp_item);
    QListWidget::startDrag(supportedActions);
}

void MyListWidget::keyPressEvent(QKeyEvent *event)
{
    temp_item = currentItem();
    if(event->key()==Qt::Key_Delete)
    {
        emit itemRemoved(this->row(temp_item));
        this->takeItem(this->row(temp_item));
        delete temp_item;
    }

}
