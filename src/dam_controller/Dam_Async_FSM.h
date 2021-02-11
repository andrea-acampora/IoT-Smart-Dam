#ifndef __DAM_ASYNC_FSM__
#define __DAM_ASYNC__FSM__

#include "async_fsm.h"
#include "Light.h"
#include "ServoMotor.h"
#include "SerialConsole.h"
#include "ConsoleBT.h"
#include "Event.h"
#include "timerZero.h"

class Dam_Async_FSM : public AsyncFSM {
  
  public:
    Dam_Async_FSM(Light* led, ServoMotor* servo, SerialConsole* console, ConsoleBT* consoleBT);
    void handleEvent(Event* ev);
     
  private:
    Light* led;
    ServoMotor* servo;
    SerialConsole* console;
    ConsoleBT* consoleBT;
    bool receivingData;
    enum  { ON, OFF} currentState;
    void openDam(int dam_opening_level);
};

#endif;
