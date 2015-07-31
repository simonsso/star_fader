#include "iowriter.h"
#include "targetvalues.h"
#include "rpiPWM1.h"
#include <QDebug>

IOWriter::IOWriter(class targetvalues *tgt){
    t=tgt;
    internal = new targetvalues();
}
IOWriter::~IOWriter(){
}
void IOWriter::run(){
    //TODO use targetvalue as increment give maxint to force on now.
    int dutycycle=0;
    rpiPWM1 pwm(100.0, 8192, 1e-5, rpiPWM1::MSMODE);
    pwm.setDutyCycleCount(0);

    //loop forever
    while(1){
        dutycycle+=t->getT();
        if(dutycycle <0 ){
            dutycycle=0; //Zero
        }else if (dutycycle >8192){
            dutycycle=8192;
        }

        pwm.setDutyCycleCount(dutycycle);
        t->status=pwm.getDutyCycle();
        usleep(50000*t->getDiv());
    }
}
