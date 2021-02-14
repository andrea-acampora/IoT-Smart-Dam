#include "SerialConsole.h"

SerialConsole::SerialConsole(){
  bindInterrupt(SERIAL_RX_PIN);
}

void SerialConsole::notifyInterrupt(){
    while (Serial.available()) {
    char ch = (char) Serial.read();
      if(ch !='\n'){
         this -> content += ch;  
      }
      if(this -> content.substring(this -> content.length() -1,content.length())=="F"){
        this -> content = this->content.substring(0,this -> content.length() -1);
        Event* msgReceived;
      if(content.substring(0,1) == "P"){
           msgReceived = new MsgReceivedEvent(MSG_DAM_OPENING,content.substring(2));
      }else if(content.substring(0,1) == "M"){
           msgReceived = new MsgReceivedEvent(MSG_MODE_CHANGED,content.substring(2));
       }else if(content == "START"){
           msgReceived = new MsgReceivedEvent(COMUNICATION_INFO, content);
       }
       else if(content == "STOP"){
           msgReceived = new MsgReceivedEvent(COMUNICATION_INFO, content);
       }
      this -> generateEvent(msgReceived);
      this -> content = ""; 
      }   
    }
}
