#ifndef __CONSOLEBT__
#define __CONSOLEBT__

#include "Event.h"
#include "MsgReceivedEvent.h"
#include "EventSource.h"
#include <AltSoftSerial.h>


#define RX_PIN 8
#define TX_PIN 9


class ConsoleBT : public EventSource{

    String content;
    AltSoftSerial channel;
    
    public:
        ConsoleBT();
        void notifyInterrupt();

}; 

#endif
