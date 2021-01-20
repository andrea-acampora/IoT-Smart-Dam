#include "TrackingTask.h"


TrackingTask::TrackingTask(Hydrometer* hydrometer, WaterLevel* waterLevel){
    this->hydrometer = hydrometer; 
    this->waterLevel = waterLevel; 
}

void TrackingTask::init(int period){
    Task::init(period); 
    state = ON; 
}

void TrackingTask::tick(){
    switch (state)
    {
    case ON:
        waterLevel->setWaterLevel(this->hydrometer->getCurrentWaterLevel()); 
        break;
    
    case OFF:
        this->setActive(false);
        break; 
    }
}
