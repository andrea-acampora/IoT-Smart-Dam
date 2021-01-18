#ifndef SENDINGTASK
#define SENDINGTASK

#include "Task.h"


//questa classe potrebbe usare un altro oggetto che implementa la comunicazione via http/mqtt

class SendingTask : public Task
{
private:
    enum {ON, OFF} state; 
    void sendData();

public:
    SendingTask();
    void tick(); 
    void init(int period); 
};

#endif