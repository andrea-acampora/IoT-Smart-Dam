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
          int dam_opening_level = ev -> getMessage().toInt();
          this -> openDam(dam_opening_level);
        }else if(ev -> getType() == MSG_MODE_CHANGED){
          if(ev->getMessage() == "MANUAL"){
            this -> led -> switchOn();
            timer0.stop();
          }else if(ev -> getMessage() == "AUTOMATIC"){
            this -> led -> switchOff();
            timer0.start();
          }
        }else if(ev -> getType() == TIMER_EVENT){
          this -> led -> isOn() ? this -> led -> switchOff() : this -> led -> switchOn();
        }else if(ev -> getType() == COMUNICATION_INFO){
          if(ev->getMessage() == "START"){
            this -> receivingData = true;
            timer0.start();
          }else if(ev -> getMessage() == "STOP"){
            this -> receivingData = false;
            timer0.stop();
          }
        }
        break;
  }
}

void Dam_Async_FSM::openDam(int dam_opening_level){
      this -> servo -> on();
      for (int i = 0; i < dam_opening_level*1.8; i++) {
          Serial.println("");
           this -> servo->setPosition(i);
      }
      this -> servo -> off();
}
