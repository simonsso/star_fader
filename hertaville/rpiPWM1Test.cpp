#include "rpiPWM1.h"


int main (void){
        
    rpiPWM1 pwm(100.0, 8191, 1e-5, rpiPWM1::MSMODE);
    pwm.setDutyCycleCount(0);
    usleep(500000);
    // initialize PWM1 output to 1KHz 8-bit resolution 80% Duty Cycle & PWM mode is MSMODE
    unsigned int dcyccount = 0; // reset Duty Cycle to Zero
    while(dcyccount < 4*2048){
        pwm.setDutyCycleCount(dcyccount); // increase Duty Cycle by 16 counts every two seconds
        dcyccount += 1;// until we hit 256 counts or 100% duty cycle
        printf("Duty Cycle is %3.2lf \n",pwm.getDutyCycle());
        printf("Divisor is %d\n", pwm.getDivisor());
        printf("dcyccount is %d\n", dcyccount);
        usleep(500);
    }
    usleep(50000000);
    return 0;
}
