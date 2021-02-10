#ifndef __OBSERVER__
#define __OBSERVER__

#include "Event.h"

/**
 * Class representing event observers, observing Event.
 */
class Observer {
    
  public:
    virtual void notifyEvent(Event* ev);    
};

#endif;
