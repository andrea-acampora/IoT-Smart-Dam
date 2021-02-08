#include "async_fsm.h"

AsyncFSM::AsyncFSM(){}
    
void AsyncFSM::notifyEvent(Event* ev){
    eventQueue.enqueue(ev);
}

void AsyncFSM::checkEvents(){
    noInterrupts();
    bool isEmpty = eventQueue.isEmpty();
    interrupts();

    if (!isEmpty){
      noInterrupts();
      Event* ev = eventQueue.dequeue();
      interrupts();

      if (ev != NULL){
        handleEvent(ev);
        delete ev;
      }
    }
}
