#ifndef SER_H
#define SER_H

#include <QObject>

class ser : public QObject
{
    Q_OBJECT

public:
    ser();

signals:
    void transmitindo(int);
    void procurando();
};

#endif
