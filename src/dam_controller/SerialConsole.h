#ifndef __SERIALCONSOLE__
#define __SERIALCONSOLE__

#include "EventSource.h"
#include "Event.h"
#include "MsgReceivedEvent.h"

#define SERIAL_RX_PIN 0

class SerialConsole : public EventSource{

    private:
         String content;
    
    public:
        SerialConsole();
        virtual void notifyInterrupt();
}; 

#endif
