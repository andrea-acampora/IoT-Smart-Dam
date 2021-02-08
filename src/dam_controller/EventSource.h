#ifndef __EVENTSOURCE__
#define __EVENTSOURCE__

#include "Observer.h"
#include "Event.h"

#define NUM_PINS 13

/**
 * Base class representing an event source, generating Event
 * observed by an Observer.
 */
 
class EventSource {
  public:
    void registerObserver(Observer* observer);
    virtual void notifyInterrupt(int pin);

  protected:
    void bindInterrupt(int pin);
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
    void notifyInterrupt(int pin);
  private:
    EventSource* sourceRegisteredOnPin[NUM_PINS];
    void (*notifyFunctions[NUM_PINS])() = {};
};

#endif;
