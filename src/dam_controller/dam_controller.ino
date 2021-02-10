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

int count=0;
int pos=0;
int delta=1;

void setup() {
  Serial.begin(9600);
  servo = new ServoMotor(PIN_SERVO);
  led = new Led(PIN_LED_DAM);
  console = new SerialConsole();
  consoleBT = new ConsoleBT();
  myAsincFSM = new Dam_Async_FSM(led,servo,console,consoleBT);
  initializeTimer0();
}

void loop() {
  myAsincFSM->checkEvents();
//   servo ->on();
//  for (int i = 0; i < 180; i++) {
//    servo->setPosition(pos);         
//    pos += delta;
//  }
//  servo ->off();
//  pos -= delta;
//  delta = -delta;
}

ISR(TIMER0_COMPA_vect){
    if(count%10==0){
          if(digitalRead(4)==HIGH){
          digitalWrite(4,LOW);
    }else{
          digitalWrite(4,HIGH);
    }    
}
  count++;
}

void initializeTimer0(){
    noInterrupts(); 
  TCCR0A = 0;// set entire TCCR0A register to 0
  TCCR0B = 0;// same for TCCR0B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  OCR0A = 255;// = (16*10^6) / (2000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  //PRESCALER 1024
  TCCR0B =(1<<CS12)|(1<<CS10);
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);
  interrupts();
}
