#ifndef GLOBALS_H
#define GLOBALS_H


#define SERIALBAUDRATE 9600

#define ACQUISITION_FREQUENCY 500
#define REPORTING_FREQUENCY 5000
#define WEATHER_CHECK_FREQUENCY 100

#define GROVE01_addr 0x02
#define GROVE02_addr 0X03

#define DUST A5
#define DUST_LED 31
#define SONAR_1_TRIG 41
#define SONAR_1_ECHO 43
#define SONAR_2_TRIG 37
#define SONAR_2_ECHO 39
#define GAS1_A A7
#define GAS1_D 35
#define GAS2_A A6
#define GAS2_D 33
#define UV A4

//POSITION OF ALL THE DATA IN THE ARRAY
#define DUST_VAL 0
#define SONAR1_VAL 1
#define SONAR2_VAL 2
#define GAS1_VAL 3
#define GAS2_VAL 4
#define UV_VAL 5
#define LUX_VAL 6
#define LIGHT 7
#define CO 8
#define NO2 9
#define C2H5OH 10
#define VOC 11

#define DEBUG_LED 13

#define DATABUFFSZIE 12

bool LEDSTATE=true;
#define ERRORBLINK 100
#define ALRIGHTBLINK 300

int collectedData[14];
String inData;
String weatherReport;



#endif