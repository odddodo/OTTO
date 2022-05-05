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

}

void outputData2Serial(){

}

Ticker blinkingSlow(blink,ALRIGHTBLINK);
Ticker blinkingFast(blink,ERRORBLINK);

#endif