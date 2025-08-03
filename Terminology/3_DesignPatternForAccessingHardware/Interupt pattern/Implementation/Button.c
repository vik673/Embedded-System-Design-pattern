#include "Button.h"
#include <stdio.h>
#include <stdlib.h>

struct Button Button_Create(void) {
    struct Button button;
    button.state = 0;       // Initially released
    button.pin = 2;         // Default pin
    button.lastState = 0;   // Previous state
    return button;
}

int Button_IsPressed(struct Button* self) {
    if (self != NULL) {
        return self->state;
    }
    return 0;
}

int Button_IsReleased(struct Button* self) {
    if (self != NULL) {
        return !self->state;
    }
    return 1;
}

void Button_Update(struct Button* self) {
    if (self != NULL) {
        self->lastState = self->state;
        // In real embedded system: self->state = digitalRead(self->pin);
        // For simulation, we'll leave this empty
    }
}

void Button_Destroy(struct Button* self) {
    // Cleanup if needed
    if (self != NULL) {
        self->state = 0;
        self->pin = 0;
        self->lastState = 0;
    }
}
