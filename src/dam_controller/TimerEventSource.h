#ifndef __TIMEREVENTSOURCE__
#define __TIMEREVENTSOURCE__

#include "EventSource.h"
#include "Event.h"
#include "TimerEvent.h"

#define N_INTERRUPT_BEFORE_EVENT 200


class TimerEventSource : public EventSource{
    private:
        int interruptCount;
    public:
        TimerEventSource();
        virtual void notifyInterrupt(int pin);
}; 

#endif
