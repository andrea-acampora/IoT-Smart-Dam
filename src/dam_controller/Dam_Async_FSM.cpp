#include "Dam_Async_FSM.h"


Dam_Async_FSM :: Dam_Async_FSM(Light* led, ServoMotor* servo, SerialConsole* console, ConsoleBT* consoleBT){
  currentState = ON;
  this -> led = led;
  this -> servo = servo;
  this -> console = console;
  this -> consoleBT = consoleBT;
  this -> console -> registerObserver(this);
  this -> consoleBT -> registerObserver(this);
}

void Dam_Async_FSM::handleEvent(Event* ev){
  switch(currentState){
    case OFF:
        break;
    case ON:
        if(ev -> getType() == MSG_DAM_OPENING){
          Serial.println(String(ev->getMessage()));
          int dam_opening_level = ev -> getMessage().toInt();
          this -> openDam(dam_opening_level);
          //FARE LAMPEGGIARE IL LED PERCHÈ SEI IN STATO ALLARME ---- TO-DO !!!!!!!!!!!!!!
        }else if(ev -> getType() == MSG_MODE_CHANGED){
          if(ev->getMessage() == "MANUAL"){
            this -> led -> switchOn();
          }else if(ev -> getMessage() == "AUTO"){
            this -> led -> switchOff();
          }
        }
        break;
  }
}

void Dam_Async_FSM::openDam(int dam_opening_level){
      this -> servo -> on();
      for (int i = 0; i < dam_opening_level*1.8; i++) {
           this -> servo->setPosition(i);         
           delay(10);            
      }
      //this -> servo -> setPosition(dam_opening_level*1.8);
      this -> servo -> off();
}
