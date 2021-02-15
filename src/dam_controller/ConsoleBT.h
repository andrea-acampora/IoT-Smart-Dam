#ifndef __CONSOLEBT__
#define __CONSOLEBT__

#include "Event.h"
#include "MsgReceivedEvent.h"
#include "EventSource.h"
#include "globals.h"
#include <AltSoftSerial.h>

class ConsoleBT : public EventSource{

    String content;
    AltSoftSerial channel;
    
    public:
        ConsoleBT();
        void notifyInterrupt();

}; 

#endif
