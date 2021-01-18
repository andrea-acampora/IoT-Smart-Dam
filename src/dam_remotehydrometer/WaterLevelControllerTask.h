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
    Task* trackingTask; 
    Task* sendingTask; 
    Task* blinkingTask; 
    WaterLevel* waterLevel; 
public:
    WaterLevelControllerTask(Task* trackingTask,Task* sendingTask, Task* blinkingTask, WaterLevel* waterLevel);
    void init(int period); 
    void tick(); 
};

#endif
