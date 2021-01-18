#ifndef WATER_LEVEL
#include WATER_LEVEL

#define PRE_ALARM_LEVEL 30 //a caso
#define ALARM_LEVEL 70 //a caso

class WaterLevel
{
private:
    enum {NORMAL, PRE_ALARM, ALARM} state; 
    float level;
    void setState(); 
public:
    WaterLevel();
    float getWaterLevel(); 
    float getState(); 
    void setWaterLevel(float level); 
};
#endif