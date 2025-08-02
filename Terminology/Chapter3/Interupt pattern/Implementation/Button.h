#ifndef Button_H
#define Button_H

// Button structure definition
struct Button {
    int state;      // 0 = released, 1 = pressed
    int pin;        // GPIO pin number
    int lastState;  // Previous state for edge detection
};

// Button operations
struct Button Button_Create(void);
int Button_IsPressed(struct Button* self);
int Button_IsReleased(struct Button* self);
void Button_Update(struct Button* self);
void Button_Destroy(struct Button* self);

#endif
