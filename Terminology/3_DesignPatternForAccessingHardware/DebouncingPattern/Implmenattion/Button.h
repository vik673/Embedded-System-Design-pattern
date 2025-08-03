#ifndef Button_H
#define Button_H

struct ButtonDriver;

typedef struct Button Button;
struct Button {
    unsigned char deviceState;  /* 0 = released, 1 = pressed */
    unsigned char backlightState;  /* 0 = off, 1 = on */
    struct ButtonDriver* itsButtonDriver;
};

/* Constructor and Destructor */
void Button_Init(Button* const me);
void Button_Cleanup(Button* const me);
Button* Button_Create(void);
void Button_Destroy(Button* const me);

/* Operations */
unsigned char Button_getState(const Button* const me);
void Button_setState(Button* const me, unsigned char state);
void Button_backlight(Button* const me, unsigned char state);
void Button_pressButton(Button* const me);  /* Simulate button press */
void Button_releaseButton(Button* const me);  /* Simulate button release */

/* Association management */
struct ButtonDriver* Button_getItsButtonDriver(const Button* const me);
void Button_setItsButtonDriver(Button* const me, struct ButtonDriver* p_ButtonDriver);
void Button___setItsButtonDriver(Button* const me, struct ButtonDriver* p_ButtonDriver);
void Button__setItsButtonDriver(Button* const me, struct ButtonDriver* p_ButtonDriver);
void Button__clearItsButtonDriver(Button* const me);

#endif
