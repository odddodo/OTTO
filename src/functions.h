#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <globals.h>
#include <Wire.h>
#include <Ticker.h>
#include <Arduino.h>



void initHardware(){
    
Serial.begin(SERIALBAUDRATE);

pinMode(GAS135_D,INPUT);
pinMode(GAS2_D,INPUT);
pinMode(DEBUG_LED,OUTPUT);


}

void blink(){

    digitalWrite(DEBUG_LED,ledON);
    ledON=!ledON;
}

void collectSensorData(){

}

void outputData2Serial(){

}

Ticker blinkingSlow(blink,1000);
Ticker blinkingFast(blink,500);

#endif