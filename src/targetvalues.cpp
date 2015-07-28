#include "targetvalues.h"
#include <QDebug>

targetvalues::targetvalues(){
    targettime=0;
    targetvalue=0;
    status=0;
}

targetvalues::~targetvalues(){
}

void targetvalues::setT(int target){
    targetvalue=target;
}
int targetvalues::getT(){
    return(targetvalue);
}
