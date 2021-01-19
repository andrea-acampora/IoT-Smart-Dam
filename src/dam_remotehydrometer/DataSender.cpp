#include "Arduino.h"
#include "DataSender.h"

DataSenderClass DataSender;
void DataSenderClass::init(String address)
{
  this->address = address;
}

void DataSenderClass::sendData(float value,String state)
{
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.print("Sending " + String(value) + "...");
    HTTPClient http;
    http.begin(this -> address + "/api/data");
    http.addHeader("Content-Type", "application/json");
    String msg = String("{ \"value\": ") + String(value) +", \"state\": \"" + state + "\" }";
    int retCode = http.POST(msg);
    http.end();
   if (retCode == 200){
     Serial.println("OK");   
   } else {
     Serial.println("ERROR");
   }
  }
}
