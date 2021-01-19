#include "WaterLevelControllerTask.h"

WaterLevelControllerTask::WaterLevelControllerTask(Task* trackingTask,Task* sendingTask,Task* blinkingTask, WaterLevel* waterLevel, Light* led_alarm){
    this->trackingTask = trackingTask; 
    this->sendingTask = sendingTask; 
    this->blinkingTask = blinkingTask; 
    this->waterLevel = waterLevel; 
    this -> led_alarm = led_alarm;
}

void WaterLevelControllerTask::init(int period){
    Task::init(period); 
    state = START; 
}

void WaterLevelControllerTask::tick(){
    switch (state)
    {
    case START:
        this->trackingTask->setActive(true);
        this->sendingTask->setActive(true);
        this->blinkingTask->setActive(true);
        this->state = WORKING; 
        break;

    case WORKING:
        if(this->waterLevel->isNormal()){
            this->led_alarm->switchOff();
            this->blinkingTask->setActive(false); 
            this->sendingTask->setActive(false);
        }else if(this->waterLevel->isPreAlarm()){
            this->blinkingTask->setActive(true); 
            //settare frequenza di sending
            this->sendingTask->setActive(true); 
        }else if(this->waterLevel->isAlarm()){
            this->blinkingTask->setActive(false); 
            this->led_alarm->switchOn();
            //settare frequenza di sending 
            this->sendingTask->setActive(true); 
        }
        break;
    } 
}
