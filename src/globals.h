#ifndef GLOBALS_H
#define GLOBALS_H


#define SERIALBAUDRATE 9600

#define ACQUISITION_FREQUENCY 5000
#define REPORTING_FREQUENCY 5000

#define PARTICLE A0
#define SONAR_1 22
#define SONAR_2 23
#define GAS135_A A1
#define GAS135_D 24
#define GAS2_A A2
#define GAS2_D 25
#define UV A3

#define DEBUG_LED 13

#define DATABUFFSZIE 12

bool LEDSTATE=true;
#define ERRORBLINK 200
#define ALRIGHTBLINK 1000

int collectedData[12];

#endif