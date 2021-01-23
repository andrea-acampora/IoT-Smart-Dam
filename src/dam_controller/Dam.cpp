#include "Dam.h"

Dam::Dam(){ 
    this->dam = new ServoMotor(PIN_SERVO); 
    this-> opening_level = 0;
}

void Dam::setOpeningLevel(int opening_level){
    this->opening_level = opening_level;
}

void Dam::openDam(){
    this->dam->setPosition(this->opening_level*1.8); 
}; 
