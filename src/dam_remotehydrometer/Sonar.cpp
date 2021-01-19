#include "Sonar.h"

Sonar::Sonar(int trigPin, int echoPin, Temp* tempSensor,float groundDistance){
   this->trigPin = trigPin; 
   this->echoPin = echoPin; 
   this->tempSensor = tempSensor; 
   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);
   this->groundDistance = groundDistance;
}

float Sonar::getDistance(){
    const float vs = 331.45 + 0.62* this->tempSensor->getTemperature(); 

    /* invio impulso */
    digitalWrite(trigPin,LOW);
    delayMicroseconds(3);
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin,LOW);

    /* ricevi l’eco */
    float tUS = pulseIn(echoPin, HIGH);
    float t = tUS / 1000.0 / 1000.0 / 2;
    float d = t*vs;
    return d*100;
}

float Sonar::getCurrentWaterLevel(){
    return this->groundDistance -this->getDistance();
}

float Sonar::getGroundDistance(){
    return this->groundDistance;
}
