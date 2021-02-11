#ifndef __TIMEREVENT__
#define __TIMEREVENT__

#include "Arduino.h"
#include "Event.h"

class TimerEvent: public Event {

  public:
    TimerEvent(int type);
    int getType();
    String getMessage();

  private:
    int type;
};


#endif;
