/**
 * @file main.c
 * @author Fredrik Simonsson
 * @brief Main
 */

/*
 * Copyright (C) 2014 Fredrik Simonsson
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <QDebug>
#include <QString>
#include <QDate>
#include <QTime>

//For sleep
#include <unistd.h>

#include "MosqConnect.h"
#include <mosquitto.h>
int main1()
{
    qDebug() << "example";

    class MosqConnect *mqtt;
    int rc;

    mosqpp::lib_init();

    mqtt = new MosqConnect(
            "star_fader",
            "localhost",
            1883
            );
    while(1)
    {
        //Check if there is new mess for me
        rc = mqtt->loop();
        if(rc)
        {
            mqtt->reconnect();
        }
    }

    mosqpp::lib_cleanup();
    return 0;
}

#include "rpiPWM1.h"


int main (void){
        
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
    return 0;
}
