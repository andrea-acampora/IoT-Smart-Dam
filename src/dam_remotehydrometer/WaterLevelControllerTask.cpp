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
        this->state = WORKING; 
        break;

    case WORKING:
        if(this -> waterLevel -> isStateChanged()){
          if(this->waterLevel->isNormal()){
            this->led_alarm->switchOff();
            this->blinkingTask->setActive(false); 
            this->sendingTask->setActive(false);
            DataSender.sendData(waterLevel -> getWaterLevel(), "NORMAL");
        }else if(this->waterLevel->isPreAlarm()){
            this->blinkingTask->setActive(true);
            this -> sendingTask -> setPeriod(FREQ_1); 
            this->sendingTask->setActive(true); 
        }else if(this->waterLevel->isAlarm()){
            this->blinkingTask->setActive(false); 
            this->led_alarm->switchOn();
            this -> sendingTask -> setPeriod(FREQ_2); 
            this->sendingTask->setActive(true); 
        }
    } 
            break;
  }
}
