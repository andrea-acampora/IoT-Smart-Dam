#include "Hydrometer.h"

Hydrometer::Hydrometer(Sonar* sonar, float groundClearance){
    this->sonar = sonar; 
    this->groundClearance = groundClearance; 
}

float Hydrometer::getCurrentWaterLevel(){
    return this->groundClearance - this->sonar->getDistance(); 
}