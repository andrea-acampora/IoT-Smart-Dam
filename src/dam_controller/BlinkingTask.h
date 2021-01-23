#ifndef __BLINKINGTASK__
#define __BLINKINGTASK__

#include "Task.h"
#include "Light.h"

/**
 * The task that manage the blinking of a led.
 */
class BlinkingTask: public Task {
  
public:
  BlinkingTask(Light* led);  
  void init(int period);
  void setActive(bool active);
  void tick();

private:
	
  Light* led;
  enum { ON, OFF } state;

};

#endif
