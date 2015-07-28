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
   qDebug() << "hello from worker thread " << thread()->currentThreadId();


/* This example code walks from 0 to 100        
    rpiPWM1 pwm(4000.0, 1024, 2e-5, rpiPWM1::MSMODE);
    // initialize PWM1 output to 1KHz 8-bit resolution 80% Duty Cycle & PWM mode is MSMODE
    usleep(1000000);

    unsigned int dcyccount = 0; // reset Duty Cycle to Zero

    while(dcyccount < 2000){
        pwm.setDutyCycleCount(dcyccount); // increase Duty Cycle by 16 counts every two seconds
        dcyccount += 1;// until we hit 256 counts or 100% duty cycle
        printf("Duty Cycle is %3.2lf \n",pwm.getDutyCycle());
        printf("Divisor is %d\n", pwm.getDivisor());
        usleep(50000);
    }
    */
    //TODO use targetvalue as increment give maxint to force on now.
    int dutycycle=0;
    rpiPWM1 pwm(4000.0, 1024, 2e-5, rpiPWM1::MSMODE);
    //loop forever
    while(1){
        dutycycle+=t->getT();
        if(dutycycle <=0 ){
            dutycycle=1; //Zero
            qDebug() << "ZERO";
        }else if (dutycycle >4000){
            dutycycle=4000; //Zero
            qDebug() << "MAXINT";
        }

        pwm.setDutyCycleCount(dutycycle++);
        printf("Duty Cycle is %3.2lf \n",pwm.getDutyCycle());
        printf("Divisor is %d\n", pwm.getDivisor());
        usleep(50000);

    }
}
