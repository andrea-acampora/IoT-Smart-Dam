#ifndef SENDINGTASK
#define SENDINGTASK

#include "Task.h"
#include "WaterLevel.h"
#include "DataSender.h"

//questa classe potrebbe usare un altro oggetto che implementa la comunicazione via http/mqtt

class SendingTask : public Task
{
private:

    WaterLevel* waterLevel;
    enum {ON, OFF} state; 

public:
    SendingTask(WaterLevel* waterLevel);
    void tick(); 
    void init(int period); 
};

#endif
