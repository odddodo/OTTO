#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <globals.h>
#include <Wire.h>
#include <Ticker.h>
#include <Arduino.h>
#include <debug.h>



void initHardware(){

Serial.begin(SERIALBAUDRATE);

pinMode(GAS135_D,INPUT);
pinMode(GAS2_D,INPUT);
pinMode(DEBUG_LED,OUTPUT);

DEBUG("alive, all set!");
}

void blink(){

    digitalWrite(DEBUG_LED,LEDSTATE);
    LEDSTATE=!LEDSTATE;
    DEBUG(LEDSTATE);
    
}

void collectSensorData(){
collectedData[0]=analogRead(PARTICLE);
collectedData[1]=analogRead(GAS135_A);
collectedData[2]=analogRead(GAS2_A);
collectedData[3]=analogRead(UV);
}

void outputData2Serial(){
DEBUG(String(collectedData[0])+","+String(collectedData[1])+","+String(collectedData[2])+","+String(collectedData[3]));
}

Ticker blinkingSlow(blink,ALRIGHTBLINK);
Ticker blinkingFast(blink,ERRORBLINK);
Ticker collect(collectSensorData,ACQUISITION_FREQUENCY);
Ticker report(outputData2Serial,REPORTING_FREQUENCY);
#endif