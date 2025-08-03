#include "Button.h"
#include "ButtonDriver.h"
#include <stdlib.h>
#include <stdio.h>

static void cleanUpRelations(Button* const me);

void Button_Init(Button* const me) {
    me->deviceState = 0;  /* Initially released */
    me->backlightState = 0;  /* Initially off */
    me->itsButtonDriver = NULL;
}

void Button_Cleanup(Button* const me) {
    cleanUpRelations(me);
}

Button* Button_Create(void) {
    Button* me = (Button*)malloc(sizeof(Button));
    if (me != NULL) {
        Button_Init(me);
    }
    return me;
}

void Button_Destroy(Button* const me) {
    if (me != NULL) {
        Button_Cleanup(me);
        free(me);
    }
}

unsigned char Button_getState(const Button* const me) {
    return me->deviceState;
}

void Button_setState(Button* const me, unsigned char state) {
    me->deviceState = state;
}

void Button_backlight(Button* const me, unsigned char state) {
    me->backlightState = state;
    printf("Button backlight %s\n", state ? "ON" : "OFF");
}

void Button_pressButton(Button* const me) {
    printf("Button pressed (hardware event)\n");
    me->deviceState = 1;
    
    /* Simulate bouncing - multiple events */
    if (me->itsButtonDriver != NULL) {
        ButtonDriver_eventReceive(me->itsButtonDriver);
    }
}

void Button_releaseButton(Button* const me) {
    printf("Button released (hardware event)\n");
    me->deviceState = 0;
    
    /* Simulate bouncing - multiple events */
    if (me->itsButtonDriver != NULL) {
        ButtonDriver_eventReceive(me->itsButtonDriver);
    }
}

struct ButtonDriver* Button_getItsButtonDriver(const Button* const me) {
    return me->itsButtonDriver;
}

void Button_setItsButtonDriver(Button* const me, struct ButtonDriver* p_ButtonDriver) {
    if (p_ButtonDriver != NULL) {
        ButtonDriver__setItsButton(p_ButtonDriver, me);
    }
    Button__setItsButtonDriver(me, p_ButtonDriver);
}

void Button___setItsButtonDriver(Button* const me, struct ButtonDriver* p_ButtonDriver) {
    me->itsButtonDriver = p_ButtonDriver;
}

void Button__setItsButtonDriver(Button* const me, struct ButtonDriver* p_ButtonDriver) {
    if (me->itsButtonDriver != NULL) {
        ButtonDriver__clearItsButton(me->itsButtonDriver);
    }
    Button___setItsButtonDriver(me, p_ButtonDriver);
}

void Button__clearItsButtonDriver(Button* const me) {
    me->itsButtonDriver = NULL;
}

static void cleanUpRelations(Button* const me) {
    if (me->itsButtonDriver != NULL) {
        ButtonDriver__clearItsButton(me->itsButtonDriver);
        me->itsButtonDriver = NULL;
    }
}
