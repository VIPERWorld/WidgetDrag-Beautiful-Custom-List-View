#ifndef QCENTEREDCELL_H
#define QCENTEREDCELL_H

#include <QStyledItemDelegate>

class QCenteredCell : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit QCenteredCell(QWidget *parent = 0);
    
signals:
    
public slots:

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // QCENTEREDCELL_H
