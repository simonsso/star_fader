#include "targetvalues.h"
#include <QDebug>
#include <QString>
#include <QDate>
#include <QTime>
#include <QThread>


#ifndef  __IOWRITER_H
#define  __IOWRITER_H

class IOWriter : public QThread
{
    class targetvalues *t;
    class targetvalues *internal;

public:
    IOWriter(class targetvalues *tgt);
    ~IOWriter();
private:
    void run();
};

#endif
