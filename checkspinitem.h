#ifndef CHECKSPINITEM_H
#define CHECKSPINITEM_H

#include <QStyledItemDelegate>
#include <QCheckBox>
#include <QSpinBox>
#include <QHBoxLayout>

class CheckSpinItem : public QWidget
{
    Q_OBJECT
public:
    explicit CheckSpinItem(QWidget *parent = 0);
    QCheckBox *check;
    QSpinBox *spin;
    QHBoxLayout *layout;
signals:
    void lengthToggled(bool);
    void lengthChanged(int);
    
public slots:
    

};

#endif // CHECKSPINITEM_H
