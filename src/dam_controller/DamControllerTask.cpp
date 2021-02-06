#include "DamControllerTask.h"
#include "Arduino.h"

DamControllerTask::DamControllerTask(BlinkingTask* blinkingTask,InputTask* inputTask,Dam* dam){ 
  this-> blinkingTask = blinkingTask;
  this->inputTask = inputTask;
  this -> dam = dam;
}

void DamControllerTask::init(int period){
  Task::init(period);
  state = ON;
}
  
void DamControllerTask::tick(){
  this->dam->openDam();
}
