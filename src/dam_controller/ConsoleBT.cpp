#include "ConsoleBT.h"

ConsoleBT::ConsoleBT(){
  content.reserve(256);
  channel.begin(9600);
  bindInterrupt(BT_RX_PIN);
}

void ConsoleBT::notifyInterrupt(){
    while (this -> channel.available()) {
      char ch = (char) this -> channel.read();
      this -> content += ch;  
      if(this -> content.substring(this -> content.length() -1)=="F"){
        this -> content = this->content.substring(0,this -> content.length() -1);
        Event* msgReceived = new MsgReceivedEvent(MSG_DAM_OPENING,content.substring(2));
        this -> generateEvent(msgReceived);
        this -> content = ""; 
      }
     }   
}

  
