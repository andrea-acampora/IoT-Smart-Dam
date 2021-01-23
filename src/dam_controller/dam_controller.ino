#include "Scheduler.h"
#include "Arduino.h"
#include "Task.h"
#include "BlinkingTask.h"
#include "DamControllerTask.h"
#include "InputTask.h"
#include "Light.h"
#include "globals.h"
#include "Led.h"
#include "Dam.h"
#include "MsgService.h"


Scheduler sched;

Task* blinkingTask;
Task* damControllerTask;
Task* inputTask;

Light* led_dam;
Dam* dam;



void setup() { 
  MsgService.init();
  sched.init(100);
  createComponents();
  createTasks();
  initTasks();
  addTasks();                 
}

   
void loop() {
   sched.schedule();
}

void createComponents(){
  led_dam= new Led(PIN_LED_DAM);
  dam = new Dam();
}

void createTasks(){
  blinkingTask = new BlinkingTask(led_dam);
  inputTask = new InputTask(dam);
  damControllerTask = new DamControllerTask(blinkingTask,inputTask,dam);
}

void initTasks(){
  blinkingTask -> init(200);
  inputTask -> init(100);
  damControllerTask -> init(100);
}


void addTasks(){
  sched.addTask(damControllerTask);
  sched.addTask(blinkingTask);
}
