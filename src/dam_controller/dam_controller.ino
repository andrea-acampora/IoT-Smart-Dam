#include "Dam_Async_FSM.h"
#include "Light.h"
#include "Led.h"
#include "ServoMotor.h"
#include "globals.h"
#include "SerialConsole.h"
#include "ConsoleBT.h"
#include "TimerOne.h"

Light* led; 
SerialConsole* console;
ConsoleBT* consoleBT;
ServoMotor* servo;

Dam_Async_FSM* myAsincFSM;

void setup() {
  Serial.begin(9600);
  servo = new ServoMotor(PIN_SERVO);
  led = new Led(PIN_LED_DAM);
  console = new SerialConsole();
  consoleBT = new ConsoleBT();
  myAsincFSM = new Dam_Async_FSM(led,servo,console,consoleBT);

}

void loop() {
  myAsincFSM->checkEvents();
}
