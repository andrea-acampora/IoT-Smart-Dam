#ifndef __DAM_ASYNC_FSM__
#define __DAM_ASYNC__FSM__

#include "async_fsm.h"
#include "Light.h"
#include "Dam.h"
#include "SerialConsole.h"
#include "ConsoleBT.h"
#include "Event.h"
#include "timerZero.h"
#include "TimerEventSource.h"


class Dam_Async_FSM : public AsyncFSM {
  
  public:
    Dam_Async_FSM(Light* led, Dam* dam, SerialConsole* console, ConsoleBT* consoleBT,TimerEventSource* timerEventSource);
    void handleEvent(Event* ev);
     
  private:
    Light* led;
    Dam* dam;
    SerialConsole* console;
    ConsoleBT* consoleBT;
    TimerEventSource* timerEventSource;
    bool receivingData;
    enum  { ON, OFF} currentState;
    void openDam(int dam_opening_level);
};

#endif;
