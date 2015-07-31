#include "iowriter.h"
#include "targetvalues.h"
#include "rpiPWM1.h"
#include <QMutex>
#include <QDebug>

IOWriter::IOWriter(class targetvalues *tgt){
    t=tgt;
    dutycycle=0;
}
IOWriter::~IOWriter(){
}
// Set dutycycle raw - TODO: caller should not need to know internal max
void IOWriter::setDutyCycle(int dc){
   mutex.lock();
   dutycycle=dc;
   mutex.unlock();
}

void IOWriter::run(){
    //TODO use targetvalue as increment give maxint to force on now.
    rpiPWM1 pwm(100.0, 8192, 1e-5, rpiPWM1::MSMODE);
    pwm.setDutyCycleCount(0);

    //loop forever
    while(1){
        mutex.lock();
        int sleeptimer=t->getDiv();
        dutycycle+=t->getT();
        if(dutycycle <0 ){
            dutycycle=0; //Zero
        }else if (dutycycle >8192){
            dutycycle=8192;
        }

        pwm.setDutyCycleCount(dutycycle);
        t->status=pwm.getDutyCycle();
        mutex.unlock();
        usleep(50000*sleeptimer);
    }
}
