#include "WaterLevel.h"


WaterLevel::WaterLevel(){}

float WaterLevel::getWaterLevel(){
    return this->level; 
}

void WaterLevel::setWaterLevel(float level){
    this->level = level; 
    this->setState(); 
}

bool WaterLevel::isNormal(){
  return this->state==NORMAL;
}

bool WaterLevel::isPreAlarm(){
  return this->state==PRE_ALARM;
}

bool WaterLevel::isAlarm(){
  return this->state==ALARM;
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

String WaterLevel::getState(){
  if(this->isNormal()){
    return "NORMAL";
  }else if(this->isPreAlarm()){
    return "PRE_ALARM";
  }else if(this->isAlarm()){
    return "ALARM";
  }
}
