#ifndef __INPUTTASK__
#define __INPUTTASK__

#include "Task.h"
#include "Dam.h"
#include "MsgService.h"

class InputTask: public Task {
  
public:
  InputTask(Dam* dam);  
  void init(int period);
  void tick();

private:
	  Dam* dam;
	  enum { ON, OFF } state;

};

#endif
