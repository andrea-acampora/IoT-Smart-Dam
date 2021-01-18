#include "WaterLevelControllerTask.h"

WaterLevelControllerTask::WaterLevelControllerTask(Task* trackingTask,Task* sendingTask,Task* blinkingTask, WaterLevel* waterLevel){
    this->trackingTask = trackingTask; 
    this->sendingTask = sendingTask; 
    this->blinkingTask = blinkingTask; 
    this->waterLevel = waterLevel; 
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
        this->state = WORKING; 
        break;

    case WORKING:
        if(this->waterLevel->isNormal()){
            this->blinkingTask->setActive(false); 
            this->sendingTask->setActive(false); 
        }else if(this->waterLevel->isPreAlarm()){
            this->blinkingTask->setActive(true); 
            //settare frequenza di sending
            this->sendingTask->setActive(true); 
        }else if(this->waterLevel->isAlarm()){
            this->blinkingTask->setActive(false); 
            //settare frequenza di sending 
            this->sendingTask->setActive(true); 
        }
        break;
    } 
}
