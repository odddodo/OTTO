#ifndef DEBUG_H
#define DEBUG_H

extern int debugging_enabled;

#define DEBUG(x)                \
    do                          \
    {                           \
        if(debugging_enabled){  \
            Serial.println(x);  \
        }                       \
    } while (0);

#endif
    