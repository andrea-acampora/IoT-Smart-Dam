#ifndef __TIMEREVENTSOURCE__
#define __TIMEREVENTSOURCE__

#include "EventSource.h"
#include "Event.h"
#include "TimerEvent.h"

#define N_INTERRUPT_BEFORE_EVENT 10


class TimerEventSource : public EventSource{
    private:
        int interruptCount;
    public:
        TimerEventSource();
        virtual void notifyInterrupt();
}; 

#endif
