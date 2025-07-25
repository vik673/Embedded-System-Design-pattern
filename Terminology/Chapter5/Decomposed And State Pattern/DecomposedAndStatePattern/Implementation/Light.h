#ifndef Light_H
#define Light_H

#include "LightPkg.h"

typedef struct Light Light;
struct Light {
    int isOn;
    ColorType color;
    FlashType mode;
};

void Light_Init(Light* const me);
void Light_Cleanup(Light* const me);
void Light_turnOn(Light* const me);
void Light_turnOff(Light* const me);
void Light_setColor(Light* const me, ColorType color);
void Light_setMode(Light* const me, FlashType mode);
int Light_isOn(const Light* const me);
ColorType Light_getColor(const Light* const me);
FlashType Light_getMode(const Light* const me);
Light * Light_Create(void);
void Light_Destroy(Light* const me);

#endif
