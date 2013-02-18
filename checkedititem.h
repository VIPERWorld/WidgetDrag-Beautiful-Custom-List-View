#ifndef CHECKEDITITEM_H
#define CHECKEDITITEM_H

#include <QStyledItemDelegate>
#include <QCheckBox>
#include <QLineEdit>
#include <QHBoxLayout>

class CheckEditItem : public QWidget
{
    Q_OBJECT
public:
    explicit CheckEditItem(QWidget *parent = 0);
    QCheckBox *check;
    QLineEdit *edit;
    QHBoxLayout *layout;
signals:
    void matchToggled(bool);
    void matchChanged(QString);

public slots:
    
};

#endif // CHECKEDITITEM_H
