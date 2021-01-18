#ifndef WATER_LEVEL
#define WATER_LEVEL

#define PRE_ALARM_LEVEL 30 //a caso
#define ALARM_LEVEL 70 //a caso
#include "Arduino.h"

class WaterLevel
{
private:
    enum {NORMAL, PRE_ALARM, ALARM} state; 
    float level;
    void setState(); 
public:
    WaterLevel();
    float getWaterLevel(); 
    bool isNormal();
    bool isPreAlarm();
    bool isAlarm();
    void setWaterLevel(float level); 
};
#endif
