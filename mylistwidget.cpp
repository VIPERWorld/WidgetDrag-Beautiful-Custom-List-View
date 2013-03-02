#include "mylistwidget.h"

MyListWidget::MyListWidget(QWidget *parent) :
    QListWidget(parent)
{
    setAcceptDrops(true);
    setDragEnabled(true);
    setDragDropMode(QAbstractItemView::InternalMove);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    QFile qss("../WidgetDrag/mylistwidget.css");
    qss.open(QFile::ReadOnly);
    setStyleSheet(qss.readAll());
    qss.close();

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
