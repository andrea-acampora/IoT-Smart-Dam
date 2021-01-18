#include "SendingTask.h"


SendingTask::SendingTask(){

}

void SendingTask::init(int period){
    Task::init(period); 
    state = OFF; 
}

void SendingTask::tick(){
    switch (state)
    {
    case ON:
        break;
    
    case OFF:
        break; 
    }
}