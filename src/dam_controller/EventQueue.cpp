#include "EventQueue.h"

EventQueue::EventQueue(){
  head = tail = 0; 
}

bool EventQueue::isEmpty() {
  return head == tail; 
}

void EventQueue::enqueue(Event* ev){
  queue[tail] = ev;
  tail = (tail+1) % MAX_EVQUEUE_SIZE;
}

Event* EventQueue::dequeue(){
    if (isEmpty()){
      return 0;
    } else {
      Event* pev = queue[head];
      head = (head+1) % MAX_EVQUEUE_SIZE;
      return pev; 
    }
}