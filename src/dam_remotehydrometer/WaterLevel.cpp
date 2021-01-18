#include "WaterLevel.h"


WaterLevel::WaterLevel(){

}

float WaterLevel::getWaterLevel(){
    return this->level; 
}

void WaterLevel::setWaterLevel(float level){
    this->level = level; 
    this->setState(); 
}

void WaterLevel::setState(){
    if(this->level > PRE_ALARM_LEVEL){
        if(this->level > ALARM_LEVEL){
            this->state = ALARM; 
        }else{
            this->state = PRE_ALARM; 
        }
    }else{
        this->state = NORMAL; 
    }
}

