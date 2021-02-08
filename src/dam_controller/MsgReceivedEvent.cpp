#include "MsgReceivedEvent.h"


MsgReceivedEvent::MsgReceivedEvent(int type, String message){
  this -> type = type;
  this -> msg = message;
}

int MsgReceivedEvent::getType(){
  return this -> type;
}


String MsgReceivedEvent::getMessage(){
  return this -> msg;
}

