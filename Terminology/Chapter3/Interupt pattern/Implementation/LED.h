#ifndef LED_H
#define LED_H

// LED structure definition
struct LED {
    int state;  // 0 = off, 1 = on
    int pin;    // GPIO pin number
};

// LED operations
struct LED LED_Create(void);
void LED_LightOn(struct LED* self);
void LED_LightOff(struct LED* self);
int LED_IsOn(struct LED* self);
void LED_Destroy(struct LED* self);

#endif
