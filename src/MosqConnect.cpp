/**
 * @file MosqConnect.cpp
 * @author Johan Simonsson
 * @brief Mosquitto interface
 */

/*
 * Copyright (C) 2014 Johan Simonsson
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

#include <cstdio>
#include <cstring>

#include <QString>
#include <QDebug>
#include <QRegExp>
#include <QDateTime>
#include <QRegExp>

#include <mosquittopp.h>

#include "MosqConnect.h"
#include "targetvalues.h"
#include "iowriter.h"

MosqConnect::~MosqConnect()
{
}
MosqConnect::MosqConnect(
        const char *id,
        const char *host,
        int port,
        class targetvalues *tgt,
        class IOWriter *myiow
        ) : mosquittopp(id)
{
    int keepalive = 60;
    t= tgt;
    iow=myiow;
    // Connect immediately.
    connect(host, port, keepalive);
};

void MosqConnect::on_connect(int rc)
{
    printf("Connected with code %d.\nsubscribed -t /starfader/\n", rc);
    if(rc == 0){
        // Only attempt to subscribe on a successful connect.
	subscribe(NULL,"/starfader/");
    }
}

void MosqConnect::on_message(const struct mosquitto_message *message)
{
    /*
       struct mosquitto_message{
       int mid;
       char *topic;
       void *payload;
       int payloadlen;
       int qos;
       bool retain;
       };
       */

    //Move from "void* with payloadlen" to a QString.
    char* messData = (char*)malloc(sizeof(char)*(message->payloadlen+1));
    memcpy(messData, message->payload, message->payloadlen);
    messData[message->payloadlen] = '\0';

    //printf("Message %s - %s.\n", message->topic, messData);

    QString mess = QString(messData);
    free(messData);

    QString topic = QString(message->topic);
    QString topicOut = QString("/starfader_status/");

    //qDebug() << "New message:" << (QDateTime::currentDateTime()).toString("hh:mm:ss") << topic << mess;

                QRegExp rxDuty("dutycycle ([0-9]{1,4})");
                QRegExp rxFade("fade (ON|OFF|AUTO) ([0-9]{1,})(/([1-9][0-9]*))?");
                if (mess.compare("status") == 0)
                {
                    QString mystatus;
                    mystatus.sprintf("PWM=%3.3f%%",t->status);
                    pub(topicOut,mystatus );
                }
                else if(rxFade.indexIn(mess) != -1)
                {
                    //qDebug() << "Force" << rxFade.cap(1) << rxFade.cap(2) << rxFade.cap(2).toInt();
                    if(0==rxFade.cap(1).compare("ON")){
                        t->setT(rxFade.cap(2).toInt());
                    } else if(0==rxFade.cap(1).compare("OFF")){
                        t->setT(-rxFade.cap(2).toInt());
                    }
                    qDebug()<<rxFade.cap(3)<<rxFade.cap(4);
                    // If divider is present Set it
                    // Call with 0 will set divider 
                    t->setDiv(rxFade.cap(4).toInt());
                }
                else if(rxDuty.indexIn(mess) != -1)
                {
                   iow->setDutyCycle(rxDuty.cap(1).toInt());
                }
                else
                {
                }
}

void MosqConnect::on_subscribe(int mid, int qos_count, const int *granted_qos)
{
    printf("Subscription succeeded. mid=%d qos=%d granter_qos=%d\n", mid, qos_count, *granted_qos);
}

void MosqConnect::pub(QString topic, QString subject)
{
    publish(NULL, topic.toAscii(), subject.size(), subject.toAscii());
}
