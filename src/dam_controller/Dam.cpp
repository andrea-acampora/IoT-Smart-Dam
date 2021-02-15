#include "Dam.h"

Dam::Dam(){
   this->servo = new ServoMotor(PIN_SERVO);
   this -> damOpeningLevel = 0;
}

void Dam::openDam(int newDamLevel){
    digitalWrite(2,HIGH);
    this -> servo -> on();
    if(newDamLevel > this->damOpeningLevel){
         for (int i = this->damOpeningLevel*1.8; i < newDamLevel*1.8; i++) {
          Serial.println("");
          this -> servo->setPosition(i);
         }
      }else if(newDamLevel < this->damOpeningLevel){
         for (int i = this->damOpeningLevel*1.8; i > newDamLevel*1.8; i--) {
          Serial.println("");
          this -> servo->setPosition(i);
         }
      }
      this->damOpeningLevel = newDamLevel;
      this -> servo -> off();
      digitalWrite(2,LOW);
}

int Dam::getDamOpeningLevel(){
  return this -> damOpeningLevel;
}

bool Dam::isOpen(){
  return this->damOpeningLevel > 0;
}
