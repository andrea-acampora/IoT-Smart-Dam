#ifndef __SONAR__
#define __SONAR__


#include "Arduino.h"
#include "Temp.h"


class Sonar{
  
    public:
        Sonar(int trigPin, int echoPin, Temp* tempSensor); 
        float getDistance(float temperature); 
        bool isObjectDetected(float temperature);

    private:
        Temp* tempSensor; 
        int trigPin; 
        int echoPin; 
        int maxDistance;
};

#endif
