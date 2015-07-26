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
int main()
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
