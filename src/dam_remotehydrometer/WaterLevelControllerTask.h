#ifndef WATER_LEVEL_CONTROLLER_TASK
#define WATER_LEVEL_CONTROLLER_TASK

#include "Task.h"
#include "WaterLevel.h"
#include "TrackingTask.h"
#include "SendingTask.h"
#include "BlinkingTask.h"
#include "Light.h"
#include "globals.h"
#include "DataSender.h"

class WaterLevelControllerTask : public Task
{
private:
    enum {START, WORKING} state; 
    Task* trackingTask; 
    Task* sendingTask; 
    Task* blinkingTask; 
    WaterLevel* waterLevel; 
    Light* led_alarm;
    
public:
    WaterLevelControllerTask(Task* trackingTask,Task* sendingTask, Task* blinkingTask, WaterLevel* waterLevel,Light* led_alarm);
    void init(int period); 
    void tick(); 
};

#endif
