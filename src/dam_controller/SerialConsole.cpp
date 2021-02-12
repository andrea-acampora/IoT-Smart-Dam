#include "SerialConsole.h"

SerialConsole::SerialConsole(){
  bindInterrupt(SERIAL_RX_PIN);
}

void SerialConsole::notifyInterrupt(){
    while (Serial.available()) {
    char ch = (char) Serial.read();
      if(ch!='\n'){
         this -> content += ch;  
      }
      if(this -> content.substring(this -> content.length() -1,content.length())=="F"){
        this -> content = this->content.substring(0,this -> content.length() -1);
      if(content.substring(0,1) == "P"){
           Event* msgReceived = new MsgReceivedEvent(MSG_DAM_OPENING,content.substring(2));
           this -> generateEvent(msgReceived);
      }else if(content.substring(0,1) == "M"){
         Event* msgReceived = new MsgReceivedEvent(MSG_MODE_CHANGED,content.substring(2));
         this -> generateEvent(msgReceived);
       }else if(content == "START"){
          Event* msgReceived = new MsgReceivedEvent(COMUNICATION_INFO, content);
         this -> generateEvent(msgReceived);
       }
       else if(content == "STOP"){
        Event* msgReceived = new MsgReceivedEvent(COMUNICATION_INFO, content);
         this -> generateEvent(msgReceived);
       }
      this -> content = ""; 
      }   
    }
}
