#include "targetvalues.h"
#include <QDebug>
#include <QString>
#include <QDate>
#include <QTime>
#include <QThread>
#include <QMutex>


#ifndef  __IOWRITER_H
#define  __IOWRITER_H

class IOWriter : public QThread
{
    class targetvalues *t;
    class targetvalues *internal;

public:
    IOWriter(class targetvalues *tgt);
    ~IOWriter();
    void setDutyCycle(int);
private:
    int dutycycle;
    QMutex mutex;
    void run();
};

#endif
