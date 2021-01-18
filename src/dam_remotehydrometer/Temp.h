#ifndef __TEMP__
#define __TEMP__

#include "Arduino.h"

#define VCC ((float)5)


class Temp{
    public: 
        Temp(int pin); 
        float getTemperature();
    private: 
        int pin; 
}; 

#endif
