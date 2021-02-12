#include "TimerEventSource.h"

TimerEventSource::TimerEventSource(){
  bindTimerInterrupt(10000);
}

void TimerEventSource::notifyInterrupt(int pin){
      if(this -> interruptCount % N_INTERRUPT_BEFORE_EVENT == 0){
           Event* timerEvent = new TimerEvent(TIMER_EVENT);
           this -> generateEvent(timerEvent);
      }
    this -> interruptCount++;
}
