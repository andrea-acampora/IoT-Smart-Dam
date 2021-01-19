#include "Scheduler.h"

volatile bool timerFlag;
Ticker ticker;

void timerHandler(void){
  timerFlag = true;
}

void Scheduler::init(int basePeriod){
  this->basePeriod = basePeriod;
  timerFlag = false;
  float period = basePeriod/float(1000);
  ticker.attach(period, timerHandler);
  nTasks = 0;
}

bool Scheduler::addTask(Task* task){
  if (nTasks < MAX_TASKS-1){
    taskList[nTasks] = task;
    nTasks++;
    return true;
  } 
  return false;
}

void Scheduler::resetTaskList(){
    this->nTasks = 0;
}

void Scheduler::schedule(){
  while (!timerFlag){ 
    //ESP.wdtFeed();
    delay(1);
}
  timerFlag = false;
  for (int i = 0; i < nTasks; i++){
    if (taskList[i]->isActive() && taskList[i]->updateAndCheckTime(basePeriod)){
      taskList[i]->tick();
    }
  }
}
