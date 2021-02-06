#include "ServoMotor.h"
#include "Arduino.h"

ServoMotor::ServoMotor(int pin){
  this->pin = pin;  
} 

void ServoMotor::on(){
  motor.attach(pin);    
}

void ServoMotor::setPosition(int angle){
  // 750 -> 0, 2250 -> 180 
  // 750 + angle*(2250-750)/180
  float coeff = (2250.0-750.0)/180;
  motor.write(750 + angle*coeff);              
}

void ServoMotor::off(){
  motor.detach();    
}
