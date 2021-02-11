#ifndef __EVENTSOURCE__
#define __EVENTSOURCE__

#include "Observer.h"
#include "Event.h"
#include "timerZero.h"

#define NUM_PINS 13

/**
 * Base class representing an event source, generating Event
 * observed by an Observer.
 */
 
class EventSource {
  public:
    void registerObserver(Observer* observer);
    virtual void notifyInterrupt();

  protected:
    void bindInterrupt(int pin);
    void bindTimerInterrupt(int period);
    void generateEvent(Event* ev);

    Observer* observer;
}; 

/**
 * Class binding interrupts to event sources
 */
class InterruptDispatcher {
  public:
    InterruptDispatcher();        
    void bind(int pin, EventSource* src);
    void bindTimerInterrupt(EventSource* src);
    void notifyInterrupt(int pin);
    void notifyTimerInterrupt();

  private:
    EventSource* sourceRegisteredOnPin[NUM_PINS];
    EventSource* timerEventSource;
    void (*notifyFunctions[NUM_PINS])() = {};
    void (*notifyTimerFunction)() = {};
};

#endif;
