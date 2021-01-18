#ifndef HYDROMETER
#define HYDROMETER

#include "Sonar.h"

class Hydrometer
{
private:
    Sonar* sonar; 
    float groundClearance; //distanza dal suolo 
public:
    Hydrometer(Sonar* sonar, float groundClearance);
    float getCurrentWaterLevel(); 
};



#endif