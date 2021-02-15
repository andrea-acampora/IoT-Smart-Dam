#ifndef __DAM__
#define __DAM__

#include "Arduino.h"
#include "ServoMotor.h"
#include "globals.h"

class Dam{
  
    public: 
        Dam(); 
        void openDam(int level);
        bool isOpen();
        int getDamOpeningLevel();
        
    private: 
        int damOpeningLevel;
        ServoMotor* servo;
}; 

#endif
