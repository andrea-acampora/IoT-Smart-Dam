#include "async_fsm.h"

AsyncFSM::AsyncFSM(){}
    
void AsyncFSM::notifyEvent(Event* ev){
    eventQueue.enqueue(ev);
}

void AsyncFSM::checkEvents(){
    noInterrupts();
    bool isEmpty = eventQueue.isEmpty();
    interrupts();

    if (!isEmpty){
      noInterrupts();
      Event* ev = eventQueue.dequeue();
      interrupts();

      if (ev != NULL){
        handleEvent(ev);
        delete ev;
      }
    }
}


void AsyncFSM::startSleepMode(){
  Serial.flush();
  set_sleep_mode( SLEEP_MODE_IDLE );
  power_all_disable();
  power_usart0_enable();
  sleep_mode();
  power_all_enable();
}
