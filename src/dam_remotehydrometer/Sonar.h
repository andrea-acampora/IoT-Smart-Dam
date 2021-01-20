#ifndef __SONAR__
#define __SONAR__


#include "Arduino.h"
#include "Hydrometer.h"
#include "Temp.h"

class Sonar: public Hydrometer{
  
    public:
        Sonar(int trigPin, int echoPin, Temp* tempSensor,float groundDistance); 
        bool isObjectDetected(float temperature);
        float getCurrentWaterLevel();
        float getGroundDistance();
    private:
        Temp* tempSensor; 
        int trigPin; 
        int echoPin; 
        int groundDistance;

       float getDistance(); 


};

#endif
