#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.h"
#include "Arduino.h"
#include <Ticker.h>


#define MAX_TASKS 50


class Scheduler {
  
  int basePeriod;
  int nTasks;
  Task* taskList[MAX_TASKS];
  Ticker ticker;

public:
  void init(int basePeriod);  
  virtual bool addTask(Task* task);  
  virtual void resetTaskList();
  virtual void schedule();
};

#endif
