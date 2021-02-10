#ifndef __EVENT__
#define __EVENT__

#include "Arduino.h"

#define MSG_DAM_OPENING 1
#define MSG_MODE_CHANGED 2

/**
 * Class representing an event
 */

class Event {

  public:
    virtual int getType() = 0;
    virtual String getMessage() = 0;
};

#endif
