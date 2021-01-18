#include "Sonar.h"

Sonar::Sonar(int trigPin, int echoPin, Temp* tempSensor){
   this->trigPin = trigPin; 
   this->echoPin = echoPin; 
   this->tempSensor = tempSensor; 
   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);
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
    return constrain(d, 0, MAX_OBJECT_DISTANCE);
}

// bool Sonar::isObjectDetected(){
//     return  this -> getDistance() < MAX_OBJECT_DISTANCE;
// }
