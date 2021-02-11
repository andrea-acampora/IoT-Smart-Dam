#include "TimerEvent.h"


TimerEvent::TimerEvent(int type){
  this -> type = type;
}

int TimerEvent::getType(){
  return this -> type;
}

String TimerEvent::getMessage(){}
