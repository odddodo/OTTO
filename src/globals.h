#ifndef GLOBALS_H
#define GLOBALS_H


#define SERIALBAUDRATE 9600

#define ACQUISITION_FREQUENCY 1000
#define REPORTING_FREQUENCY 1000

#define PARTICLE A0
#define SONAR_1 22
#define SONAR_2 23
#define GAS135_A A1
#define GAS135_D 24
#define GAS2_A A2
#define GAS2_D 25
#define UV A3

//POSITION OF ALL THE DATA IN THE ARRAY
#define DUST_VAL 0
#define SONAR1_VAL 1
#define SONAR2_VAL 2
#define GAS135_VAL 3
#define GAS2_VAL 4
#define UV_VAL 5
#define WIND_VAL 6
#define WIND_DIR_VAL 7
#define RAIN_VAL 8
#define HUMIDITY 9
#define PRESSURE 10
#define LIGHT 11

#define DEBUG_LED 13

#define DATABUFFSZIE 12

bool LEDSTATE=true;
#define ERRORBLINK 200
#define ALRIGHTBLINK 500

int collectedData[12];

#endif