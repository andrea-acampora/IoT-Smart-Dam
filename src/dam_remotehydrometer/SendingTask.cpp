#include "SendingTask.h"


SendingTask::SendingTask(WaterLevel* waterLevel ){
    this->waterLevel = waterLevel;
}

void SendingTask::init(int period){
    Task::init(period); 
    state = ON; 
}

void SendingTask::tick(){
    switch (state)
    {
    case ON:
        DataSender.sendData(waterLevel -> getWaterLevel(), waterLevel -> getState());
        break;
    
    case OFF:
        this -> setActive(false);
        break; 
    }
}
