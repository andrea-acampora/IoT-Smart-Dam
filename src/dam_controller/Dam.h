#ifndef __DAM__
#define __DAM__

#include "ServoMotor.h"
#include "globals.h"
#include "Arduino.h"

class Dam{
    public: 
        Dam(); 
        void setOpeningLevel(int opening_level);
        int getOpeningLevel();
        void openDam(); 
    private: 
        ServoMotor* dam;
        int opening_level;
}; 

#endif
