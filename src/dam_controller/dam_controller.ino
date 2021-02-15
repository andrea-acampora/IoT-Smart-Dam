#include "Dam_Async_FSM.h"
#include "Light.h"
#include "Led.h"
#include "Dam.h"
#include "globals.h"
#include "SerialConsole.h"
#include "ConsoleBT.h"
#include "timerZero.h"
#include "TimerEventSource.h"

Light* led; 
SerialConsole* console;
ConsoleBT* consoleBT;
Dam* dam;
TimerEventSource* timerEventSource;

Dam_Async_FSM* dam_AsincFSM;

void setup() {
  Serial.begin(9600);
  dam = new Dam();
  led = new Led(PIN_LED_DAM);
  console = new SerialConsole();
  consoleBT = new ConsoleBT();
  timerEventSource = new TimerEventSource();
  dam_AsincFSM = new Dam_Async_FSM(led,dam,console,consoleBT,timerEventSource);
}

void loop() {
  dam_AsincFSM->checkEvents();
}
