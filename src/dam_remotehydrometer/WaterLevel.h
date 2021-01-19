#ifndef WATER_LEVEL
#define WATER_LEVEL


#define PRE_ALARM_LEVEL 400 
#define ALARM_LEVEL 460
#include "Arduino.h"

class WaterLevel
{
private:
    enum {NORMAL, PRE_ALARM, ALARM} state; 
    float level;
    String getState();
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
