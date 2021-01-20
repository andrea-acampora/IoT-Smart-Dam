#ifndef __DATASENDER__
#define __DATASENDER__

#include "Arduino.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>


class DataSenderClass {
    
public: 
  
  String address;

  void init(String address);  
  
  void sendData(float value,String state);
};

extern DataSenderClass DataSender;

#endif
