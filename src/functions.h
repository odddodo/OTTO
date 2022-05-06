#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <globals.h>
#include <Wire.h>
#include <Ticker.h>
#include <Arduino.h>
#include <debug.h>



void initHardware(){

Serial.begin(SERIALBAUDRATE);

Serial3.begin(SERIALBAUDRATE);

pinMode(GAS135_D,INPUT);
pinMode(GAS2_D,INPUT);
pinMode(DEBUG_LED,OUTPUT);

DEBUG("alive, all set!");
}

void blink(){

    digitalWrite(DEBUG_LED,LEDSTATE);
    LEDSTATE=!LEDSTATE;    
    
}

void collectSensorData(){
collectedData[DUST_VAL]=analogRead(PARTICLE);
collectedData[GAS135_VAL]=analogRead(GAS135_A);
collectedData[GAS2_VAL]=analogRead(GAS2_A);
collectedData[UV_VAL]=analogRead(UV);
}

void outputData2Serial(){
DEBUG(String(collectedData[DUST_VAL])
+","+String(collectedData[GAS135_VAL])
+","+String(collectedData[GAS2_VAL])
+","+String(collectedData[UV_VAL])
+","+String(collectedData[4])
+","+String(collectedData[5])
+",WS: "+weatherReport);
}

const int BUFFER_SIZE =6;
String inData;
void listenToWeatherShield(){

   while(Serial3.available()>0){
    String received=Serial3.readStringUntil('#');
   weatherReport=received;
  
   }
}

Ticker blinkingSlow(blink,ALRIGHTBLINK);
Ticker blinkingFast(blink,ERRORBLINK);
Ticker collect(collectSensorData,ACQUISITION_FREQUENCY);
Ticker report(outputData2Serial,REPORTING_FREQUENCY);
Ticker listen(listenToWeatherShield,WEATHER_CHECK_FREQUENCY);
#endif