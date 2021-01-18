#include "WaterLevelControllerTask.h"

WaterLevelControllerTask::WaterLevelControllerTask(TrackingTask* trackingTask, SendingTask* sendingTask, BlinkingTask* blinkingTask, WaterLevel* waterLevel){
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

        switch (this->waterLevel->getState())
        {
        case NORMAL:
            this->blinkingTask->setActive(false); 
            this->sendingTask->setActive(false); 
            break;
        case PRE_ALARM:
            this->blinkingTask->setActive(true); 
            //settare frequenza di sending
            this->sendingTask->setActive(true); 
            break;
        }
        case ALARM:
            this->blinkingTask->setActive(false); 
            //settare frequenza di sending 
            this->sendingTask->setActive(true); 

        break; 
    }
}