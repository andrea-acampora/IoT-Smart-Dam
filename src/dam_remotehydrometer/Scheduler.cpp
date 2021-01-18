#include "Scheduler.h"

volatile bool timerFlag;

void timerHandler(void){
  timerFlag = true;
}

void Scheduler::init(int basePeriod){
  this->basePeriod = basePeriod;
  timerFlag = false;
  long period = basePeriod/1000;
  this->ticker.attach(period, timerHandler);
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
  while (!timerFlag){ ESP.wdtFeed();}
  timerFlag = false;
  for (int i = 0; i < nTasks; i++){
    if (taskList[i]->isActive() && taskList[i]->updateAndCheckTime(basePeriod)){
      taskList[i]->tick();
    }
  }
}
