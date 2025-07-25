#include "LED.h"
#include <stdio.h>
#include <stdlib.h>

struct LED LED_Create(void) {
    struct LED led;
    led.state = 0;  // Initially off
    led.pin = 13;   // Default pin
    return led;
}

void LED_LightOn(struct LED* self) {
    if (self != NULL) {
        self->state = 1;
        printf("LED turned ON (Pin %d)\n", self->pin);
        // In real embedded system: digitalWrite(self->pin, HIGH);
    }
}

void LED_LightOff(struct LED* self) {
    if (self != NULL) {
        self->state = 0;
        printf("LED turned OFF (Pin %d)\n", self->pin);
        // In real embedded system: digitalWrite(self->pin, LOW);
    }
}

int LED_IsOn(struct LED* self) {
    if (self != NULL) {
        return self->state;
    }
    return 0;
}

void LED_Destroy(struct LED* self) {
    // Cleanup if needed
    if (self != NULL) {
        self->state = 0;
        self->pin = 0;
    }
}
