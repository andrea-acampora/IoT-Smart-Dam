#ifndef __TIMER0__
#define __TIMER0__

#include "EventSource.h"
#include "Event.h"

class Timer0 : public EventSource{

    private:
         String content;
    
    public:
        Timer0();
        virtual void notifyInterrupt(int pin);
}; 

#endif
