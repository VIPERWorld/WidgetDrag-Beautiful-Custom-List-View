#include "qcenteredcell.h"
#include <QPainter>

QCenteredCell::QCenteredCell(QWidget *parent) :
    QStyledItemDelegate(parent)
{
//    this->setProperty()
}

void QCenteredCell::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt = option;
    opt.displayAlignment = Qt::AlignCenter;
    opt.decorationAlignment = Qt::AlignCenter;
//    QRect rect = option.rect;
    QStyledItemDelegate::paint(painter,opt,index);

}
