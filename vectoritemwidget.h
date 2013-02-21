#ifndef VECTORITEMWIDGET_H
#define VECTORITEMWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QSpinBox>
#include <QHBoxLayout>

class VectorItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VectorItemWidget(QWidget *parent = 0);
    QLineEdit *nameEdit;
    QPushButton *typeButton;
    QHBoxLayout *hLayout;

signals:
    
public slots:

private:
    
};

#endif // VECTORITEMWIDGET_H
