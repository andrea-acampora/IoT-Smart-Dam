#ifndef __DAMCONTROLLERTASK__
#define __DAMCONTROLLERTASK__

#include "Task.h"
#include "BlinkingTask.h"
#include "InputTask.h"
#include "Dam.h"


class DamControllerTask: public Task {
  
public:
  DamControllerTask(BlinkingTask* blinkingTask,InputTask* inputTask,Dam* dam);  
  void init(int period);
  void tick();

private:
	
  Dam* dam;
  BlinkingTask* blinkingTask;
  InputTask* inputTask;
  enum { ON, OFF } state;

};

#endif
