#ifndef __SERIALCONSOLE__
#define __SERIALCONSOLE__

#include "EventSource.h"
#include "Event.h"
#include "MsgReceivedEvent.h"
#include "globals.h"

class SerialConsole : public EventSource{

    private:
         String content;
    
    public:
        SerialConsole();
        virtual void notifyInterrupt();
}; 

#endif
