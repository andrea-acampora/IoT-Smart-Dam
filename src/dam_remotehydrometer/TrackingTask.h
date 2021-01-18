#ifndef TRACKING_TASK
#define TRACKING_TASK

#include "Task.h"
#include "Hydrometer.h"
#include "WaterLevel.h"

class TrackingTask : public Task
{
private:
    enum {START, ONTRACK} state; 
    Hydrometer* hydrometer; 
    WaterLevel* waterLevel; 
    void track();

public:
    TrackingTask(Hydrometer* hydrometer, WaterLevel* waterLevel);
    void tick(); 
    void init(int period); 
};
#endif