#include <ESP8266WiFi.h>
#include "Scheduler.h"
#include "Task.h"
#include "SendingTask.h"
#include "TrackingTask.h"
#include "BlinkingTask.h"
#include "WaterLevel.h"
#include "WaterLevelControllerTask.h"
#include "Sonar.h"
#include "Light.h"
#include "Temp.h"
#include "globals.h"
#include "Led.h"
#include "DataSender.h"

Scheduler sched;

WaterLevelControllerTask* waterLevelControllerTask;
Task* blinkingTask;
Task* trackingTask;
Task* sendingTask;


Light* led_alarm;
Temp* temp;
Hydrometer* hydrometer;

WaterLevel* waterLevel;

char* ssidName = "TIM-CASA";
char* pwd = "tim3d208f6e03";
char* address = "http://1d9abf9c1bed.ngrok.io";


void setup() { 
  Serial.begin(115200);
  setupWiFi(ssidName,pwd);
  sched.init(50);
  createComponents();
  createTasks();
  initTasks();
  addTasks();                 
}

   
void loop() {
   sched.schedule();
}

void createComponents(){
  DataSender.init(address);
  led_alarm = new Led(PIN_LED_ALARM);
  temp = new Temp(PIN_TEMP);
  hydrometer = new Sonar(SONAR_TRIGGER_PIN, SONAR_ECHO_PIN,temp,GROUND_DISTANCE);
  waterLevel = new WaterLevel();
}

void createTasks(){
  blinkingTask = new BlinkingTask(led_alarm);
  trackingTask = new TrackingTask(hydrometer,waterLevel);
  sendingTask = new SendingTask(waterLevel);
  waterLevelControllerTask = new WaterLevelControllerTask(trackingTask, sendingTask, blinkingTask, waterLevel,led_alarm);
}

void initTasks(){
  blinkingTask -> init(100);
  trackingTask -> init(100);
  sendingTask -> init(100);
  waterLevelControllerTask -> init(50);
  waterLevelControllerTask -> setActive(true);
}


void addTasks(){
  sched.addTask(waterLevelControllerTask);
  sched.addTask(sendingTask);
  sched.addTask(trackingTask);
  sched.addTask(blinkingTask);
}

void setupWiFi(char* ssidName,char* pwd){
    WiFi.begin(ssidName, pwd);
    Serial.print("Connecting...");
    while (WiFi.status() != WL_CONNECTED) {  
      delay(500);
      Serial.print(".");
     } 
  Serial.println("\n\n[+] Connected to: "+String(ssidName));
}
