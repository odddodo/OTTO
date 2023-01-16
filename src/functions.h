#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <globals.h>
#include <Wire.h>
#include <Ticker.h>
#include <Arduino.h>
#include <debug.h>
#include <Multichannel_Gas_GMXXX.h>
#include <Adafruit_TSL2591.h>


GAS_GMXXX<TwoWire> grove_one;
//GAS_GMXXX<TwoWire> grove_two;

Adafruit_TSL2591 tsl;

void initHardware(){

Serial.begin(SERIALBAUDRATE);
Serial3.begin(SERIALBAUDRATE);

DEBUG("initialized Serial");

pinMode(GAS1_D,INPUT);
pinMode(GAS2_D,INPUT);
pinMode(DUST_LED,OUTPUT);
pinMode(SONAR_1_TRIG,OUTPUT);
pinMode(SONAR_2_TRIG,OUTPUT);
pinMode(SONAR_1_ECHO,INPUT);
pinMode(SONAR_2_ECHO,INPUT);
pinMode(DEBUG_LED,OUTPUT);

for(int i=0;i<5;i++){
    DEBUG(".");
    delay(100);
}

grove_one.begin(Wire,0x08);
//grove_one.setAddress(GROVE01_addr);
grove_one.preheated();

DEBUG("initialized Grove 1");

for(int i=0;i<5;i++){
    DEBUG(".");
    delay(100);
}

//grove_two.begin(Wire,0x08);
//grove_two.setAddress(GROVE02_addr);
//grove_two.preheated();

//DEBUG("initialized Grove 2");
sensor_t sensor;
tsl.getSensor(&sensor);
tsl.setGain(TSL2591_GAIN_MED);
tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);
//DEBUG(tsl.getGain());

DEBUG("alive, all set!");
delay(100);
}

void blink(){
    digitalWrite(DEBUG_LED,LEDSTATE);
    LEDSTATE=!LEDSTATE;    
}

int Filter(int v){
    static int flag_first=0,_buff[DUST_BUFF_LEN],sum;
    const int _buff_max=DUST_BUFF_LEN;
    int i;

    if(flag_first==0){
        flag_first=1;
        for(i=0;i<_buff_max;i++){
            _buff[i]=v;
                  }
                  return v;
    }
                  else{
                      sum-=_buff[0];
                      for(i=0;i<(_buff_max-1);i++){
                          _buff[i]=_buff[i+1];
                      }
                      _buff[DUST_BUFF_LEN-1]=v;
                      sum+=_buff[DUST_BUFF_LEN-1];
                      i=sum/10.0;
                      return i;
                  }
    
}

int process_dust(float reading){
    if(reading>=NO_DUST_VOLT){
        reading-=NO_DUST_VOLT;
        return round(reading*0.2);
    }
    else{
        return 0;
    }
}

void collectSensorData(){
digitalWrite(DUST_LED,HIGH);
delayMicroseconds(280);
collectedData[DUST_VAL]=process_dust(Filter(analogRead(DUST))*11*(5000/1024.0));;
collectedData[GAS1_VAL]=analogRead(GAS1_A);
collectedData[GAS2_VAL]=analogRead(GAS2_A);
collectedData[UV_VAL]=analogRead(UV);
collectedData[CO]=grove_one.measure_CO();
collectedData[NO2]=grove_one.measure_NO2();
collectedData[C2H5OH]=grove_one.measure_C2H5OH();
collectedData[VOC]=grove_one.measure_VOC();
collectedData[SONAR1_VAL]=digitalRead(SONAR_1_ECHO);
collectedData[SONAR2_VAL]=digitalRead(SONAR_2_ECHO);

collectedData[FULL_VAL]=tsl.getFullLuminosity();
collectedData[VIS_VAL]=tsl.getLuminosity(TSL2591_VISIBLE);
collectedData[IR_VAL]=tsl.getLuminosity(TSL2591_INFRARED);
collectedData[LUX_VAL]=tsl.calculateLux(collectedData[FULL_VAL], collectedData[IR_VAL]);

digitalWrite(DUST_LED,LOW);

}



void outputData2Serial(){
DEBUG(String(collectedData[DUST_VAL])
+","+String(collectedData[GAS1_VAL])
+","+String(collectedData[GAS2_VAL])
+","+String(collectedData[UV_VAL])
+","+String(collectedData[FULL_VAL])
+","+String(collectedData[VIS_VAL])
+","+String(collectedData[IR_VAL])
+","+String(collectedData[LUX_VAL])
+","+String(collectedData[CO])
+","+String(collectedData[NO2])
+","+String(collectedData[C2H5OH])
+","+String(collectedData[VOC])
+","+String(collectedData[SONAR1_VAL])
+","+String(collectedData[SONAR2_VAL]));
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