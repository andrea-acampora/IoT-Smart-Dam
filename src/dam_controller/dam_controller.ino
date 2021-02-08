#include "Dam_Async_FSM.h"
#include "Light.h"
#include "Led.h"
#include "ServoMotor.h"
#include "globals.h"
#include "SerialConsole.h"
#include "ConsoleBT.h"


Light* led; 
ServoMotor* servo;
SerialConsole* console;
ConsoleBT* consoleBT;

Dam_Async_FSM* myAsincFSM;

void setup() {
  Serial.begin(9600);
  led = new Led(PIN_LED_DAM);
  servo = new ServoMotor(PIN_SERVO);
  console = new SerialConsole();
  consoleBT = new ConsoleBT();
  myAsincFSM = new Dam_Async_FSM(led,servo,console,consoleBT);
}

void loop() {
  myAsincFSM->checkEvents();
}

/*
void startSleepMode(){
  //Serial.println( "Going to sleep....\n" );
  Serial.flush();
  set_sleep_mode( SLEEP_MODE_IDLE );
  power_all_disable();
  power_usart0_enable();
  sleep_mode();
  power_all_enable();
  //Serial.println( "...Awake !\n" );
}*/
