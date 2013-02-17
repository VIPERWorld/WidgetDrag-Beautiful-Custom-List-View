#ifndef PARSERENGINE_H
#define PARSERENGINE_H

#include <QObject>

class VariableClass {
public:
    QString name;
    quint8 type;
    bool fixed;
    bool match;
    quint8 length;
    quint8 repeat;
    QString matchBytes;
    QList<QByteArray> received;
    QList<double> numValue;
};

class ParserEngine : public QObject
{
    Q_OBJECT
public:
    explicit ParserEngine(QObject *parent = 0);
    
signals:
    
public slots:

private:
    QList<VariableClass*> *variable;

};

#endif // PARSERENGINE_H
