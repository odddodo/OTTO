#include <Arduino.h>
#include <functions.h>
#include <globals.h>
#include <debug.h>

int debugging_enabled=1;

void setup() {

 initHardware();

 blinkingSlow.start();
 collect.start();
 report.start();
}

void loop() {
 blinkingSlow.update(); 
 collect.update();
 report.update();
}