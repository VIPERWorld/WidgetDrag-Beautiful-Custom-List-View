#ifndef VECTOROPSITEM_H
#define VECTOROPSITEM_H

#include <QStyledItemDelegate>
#include <QPushButton>
#include <QHBoxLayout>

class VectorOpsItem : public QWidget
{
    Q_OBJECT
public:
    explicit VectorOpsItem(QWidget *parent = 0);
    QPushButton *upButton;
    QPushButton *downButton;
    QPushButton *delButton;
    QHBoxLayout *layout;
signals:
    void moveUp();
    void moveDown();
    void removeVar();
public slots:
    

};

#endif // VECTOROPSITEM_H
