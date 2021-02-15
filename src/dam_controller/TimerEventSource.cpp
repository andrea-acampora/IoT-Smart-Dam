#include "TimerEventSource.h"

TimerEventSource::TimerEventSource(){
  bindTimerInterrupt(16000);
}

void TimerEventSource::notifyInterrupt(){
      if(this -> interruptCount % N_INTERRUPT_BEFORE_EVENT == 0){
           Event* timerEvent = new TimerEvent(TIMER_EVENT);
           this -> generateEvent(timerEvent);
      }
    this -> interruptCount++;
}
