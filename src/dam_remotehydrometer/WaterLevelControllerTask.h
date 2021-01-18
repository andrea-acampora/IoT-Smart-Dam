#ifndef WATER_LEVEL_CONTROLLER_TASK
#define WATER_LEVEL_CONTROLLER_TASK

#include "Task.h"
#include "WaterLevel.h"
#include "TrackingTask.h"
#include "SendingTask.h"
#include "BlinkingTask.h"


class WaterLevelControllerTask : public Task
{
private:
    enum {START, WORKING} state; 
    TrackingTask* trackingTask; 
    SendingTask* sendingTask; 
    BlinkingTask* blinkingTask; 
    WaterLevel* waterLevel; 
public:
    WaterLevelControllerTask(TrackingTask* trackingTask, SendingTask* sendingTask, BlinkingTask* blinkingTask, WaterLevel* waterLevel);
    void init(int period); 
    void tick(); 
};

#endif