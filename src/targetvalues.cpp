#include "targetvalues.h"
#include <QDebug>

targetvalues::targetvalues(){
    targettime=0;
    div=1;
    targetvalue=0;
    status=0;
}

targetvalues::~targetvalues(){
}

void targetvalues::setDiv(int d){
   if(d){
      //Do not divide by zero.
      //toInt used to call this will return 0 on fail
      //this is where I catch it
      div=d;
   }else{
      div=1;
   }
}
int targetvalues::getDiv(){
    return(div);
}
void targetvalues::setT(int target){
    targetvalue=target;
}
int targetvalues::getT(){
    return(targetvalue);
}
