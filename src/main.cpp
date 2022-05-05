#include <Arduino.h>
#include <functions.h>
#include <globals.h>


void setup() {

 initHardware();
 
 blinkingSlow.start();
}

void loop() {
 blinkingSlow.update(); 
}