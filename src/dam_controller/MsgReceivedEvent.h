#ifndef __MSGRECEIVEDEVENT__
#define __MSGRECEIVEDEVENT__

#include "Arduino.h"
#include "Event.h"

class MsgReceivedEvent: public Event {

  public:
    MsgReceivedEvent(int type,String message);
    int getType();
    String getMessage();

  private:
    int type;
    String msg;
};


#endif;
