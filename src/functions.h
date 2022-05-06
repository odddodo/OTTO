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
+","+String(collectedData[5]));
}

const int BUFFER_SIZE =6;

void listenToWeatherShield(){
    char buf[BUFFER_SIZE];
    if(Serial3.available()>0){
        
        Serial3.readBytesUntil('w',buf,BUFFER_SIZE);
      
            collectedData[4]=(int)buf[0];
            collectedData[5]=(int)buf[1];
        
        
    }
    else{
        collectedData[4]=0;
        
    }
}

Ticker blinkingSlow(blink,ALRIGHTBLINK);
Ticker blinkingFast(blink,ERRORBLINK);
Ticker collect(collectSensorData,ACQUISITION_FREQUENCY);
Ticker report(outputData2Serial,REPORTING_FREQUENCY);
Ticker listen(listenToWeatherShield,100);
#endif