#include "TrackingTask.h"


TrackingTask::TrackingTask(Hydrometer* hydrometer, WaterLevel* waterLevel){
    this->hydrometer = hydrometer; 
    this->waterLevel = waterLevel; 
}

void TrackingTask::init(int period){
    Task::init(period); 
    state = START; 
}

void TrackingTask::tick(){
    switch (state)
    {
    case START:
        break;
    
    case ONTRACK:
        float level = this->hydrometer->getCurrentWaterLevel(); 
        waterLevel->setWaterLevel(level); 
        break; 
    }
}