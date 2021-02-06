#include "InputTask.h"
#include "Arduino.h"

InputTask::InputTask(Dam* dam){ 
  this->dam = dam;
}

void InputTask::init(int period){
  Task::init(period);
  state = ON;
}

void InputTask::tick(){
  if(MsgService.isMsgAvailable()){
    this->dam->setOpeningLevel(MsgService.receiveMsg());
  }
}
