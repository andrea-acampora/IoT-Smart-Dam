#ifndef __ASYNC_FSM__
#define __ASYNC_FSM__

#include "Observer.h"
#include "Event.h"
#include "EventQueue.h"
#include "Arduino.h"

/**
 * Base abstract class for implementing asynchronous
 * Finite State Machines.
 * 
 * NOTES:
 * - it is an Observer of events generated by event source
 * - the state is meant to be modelled by derived classes
 */


class AsyncFSM : public Observer {
public:
  virtual void handleEvent(Event* ev) = 0;
  void notifyEvent(Event* ev);  
  void checkEvents();  

protected:
  AsyncFSM();    
  EventQueue eventQueue;
};

#endif
