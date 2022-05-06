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

for(int i=0;i<10;i++){
    DEBUG(".");
    delay(100);
}

delay(100);
DEBUG("alive, all set!");
delay(100);
}

void blink(){
    digitalWrite(DEBUG_LED,LEDSTATE);
    LEDSTATE=!LEDSTATE;    
}

void collectSensorData(){
collectedData[DUST_VAL]=analogRead(DUST);
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
+","+String(collectedData[5]));
DEBUG(weatherReport+"#");
}



void listenToWeatherShield(){
   while(Serial3.available()>0){
    String received=Serial3.readStringUntil('#');
   weatherReport=received;
   weatherReport.replace("\n","");  
   }
}




Ticker blinkingSlow(blink,ALRIGHTBLINK);
Ticker blinkingFast(blink,ERRORBLINK);
Ticker collect(collectSensorData,ACQUISITION_FREQUENCY);
Ticker report(outputData2Serial,REPORTING_FREQUENCY);
Ticker listen(listenToWeatherShield,WEATHER_CHECK_FREQUENCY);
#endif