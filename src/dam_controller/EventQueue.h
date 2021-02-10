#include "Event.h"

#define MAX_EVQUEUE_SIZE 30 

/**
 * Class representing an event queue, used inside the async FSM
 */
class EventQueue { 

    public:
        EventQueue();
        bool isEmpty();
        void enqueue(Event* ev);
        Event* dequeue();  
    private:

        Event* queue[MAX_EVQUEUE_SIZE];
        int head, tail; 
};
