#include "Light.h"
#include <stdio.h>

void Light_Init(Light* const me) {
    me->isOn = 0;
    me->color = RED;
    me->mode = STEADY;
}

void Light_Cleanup(Light* const me) {
    // Nothing to cleanup for now
}

void Light_turnOn(Light* const me) {
    me->isOn = 1;
    printf("Light: Turned ON\n");
}

void Light_turnOff(Light* const me) {
    me->isOn = 0;
    printf("Light: Turned OFF\n");
}

void Light_setColor(Light* const me, ColorType color) {
    me->color = color;
    const char* colorStr = (color == RED) ? "RED" : 
                          (color == YELLOW) ? "YELLOW" : "GREEN";
    printf("Light: Color set to %s\n", colorStr);
}

void Light_setMode(Light* const me, FlashType mode) {
    me->mode = mode;
    const char* modeStr = (mode == STEADY) ? "STEADY" : 
                         (mode == SLOWLY) ? "SLOWLY" : "QUICKLY";
    printf("Light: Mode set to %s\n", modeStr);
}

int Light_isOn(const Light* const me) {
    return me->isOn;
}

ColorType Light_getColor(const Light* const me) {
    return me->color;
}

FlashType Light_getMode(const Light* const me) {
    return me->mode;
}

Light * Light_Create(void) {
    Light* me = (Light *)malloc(sizeof(Light));
    if(me!=NULL)
        Light_Init(me);
    return me;
}

void Light_Destroy(Light* const me) {
    if(me!=NULL)
        Light_Cleanup(me);
    free(me);
}
