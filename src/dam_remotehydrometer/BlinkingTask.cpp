#include "BlinkingTask.h"
#include "Arduino.h"

/**
 * The task that manage the blinking of a led.
 */
BlinkingTask::BlinkingTask(Light* led){ 
  this->led = led;
}

void BlinkingTask::init(int period){
  Task::init(period);
  state = ON;
}
  
void BlinkingTask::setActive(bool active){
  Task::setActive(active);
  if(!active){
    led->switchOff();
  }
}

void BlinkingTask::tick(){
  switch (state){
    case ON: {
      led->switchOn();
      state = OFF;
      break;
    }
    case OFF: {
      led->switchOff();
      state = ON;
      break;
    }
  }
}
