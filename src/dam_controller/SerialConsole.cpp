#include "SerialConsole.h"

SerialConsole::SerialConsole(){
  bindInterrupt(SERIAL_RX_PIN);
}

void SerialConsole::notifyInterrupt(int pin){
    while (Serial.available()) {
    char ch = (char) Serial.read();
      this -> content += ch;  
      if(this -> content.substring(this -> content.length() -1)=="F"){
        this -> content = this->content.substring(0,this -> content.length() -1);
      if(content.substring(0,1) == "P"){
           Event* msgReceived = new MsgReceivedEvent(MSG_DAM_OPENING,content.substring(2));
           this -> generateEvent(msgReceived);
           this -> content = ""; 
      }else if(content.substring(0,1) == "M"){
         Event* msgReceived = new MsgReceivedEvent(MSG_MODE_CHANGED,content.substring(2));
         this -> generateEvent(msgReceived);
         this -> content = ""; 
       }
      }   
    }
}
