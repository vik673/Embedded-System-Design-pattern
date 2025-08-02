#include "ButtonDriver.h"
#include "Button.h"
#include "MicrowaveEmitter.h"
#include "Timer.h"
#include <stdio.h>

static void cleanUpRelations(ButtonDriver* const me);

void ButtonDriver_Init(ButtonDriver* const me) {
    me->oldState = 0;
    me->toggleOn = 0;
    me->itsButton = NULL;
    me->itsMicrowaveEmitter = NULL;
    me->itsTimer = NULL;
}

void ButtonDriver_Cleanup(ButtonDriver* const me) {
    cleanUpRelations(me);
}

ButtonDriver* ButtonDriver_Create(void) {
    ButtonDriver* me = (ButtonDriver*)malloc(sizeof(ButtonDriver));
    if (me != NULL) {
        ButtonDriver_Init(me);
    }
    return me;
}

void ButtonDriver_Destroy(ButtonDriver* const me) {
    if (me != NULL) {
        ButtonDriver_Cleanup(me);
        free(me);
    }
}

void ButtonDriver_eventReceive(ButtonDriver* const me) {
    printf("ButtonDriver: Event received, starting debounce...\n");
    
    /* Wait for debounce period */
    Timer_delay(me->itsTimer, DEBOUNCE_TIME);
    
    /* Check if state has actually changed after debounce period */
    if (Button_getState(me->itsButton) != me->oldState) {
        printf("ButtonDriver: Valid state change detected!\n");
        
        /* Update the old state */
        me->oldState = Button_getState(me->itsButton);
        
        if (!me->oldState) {
            /* Button release event - this is when we toggle */
            printf("ButtonDriver: Button released - toggling microwave\n");
            
            if (me->toggleOn) {
                /* Toggle OFF */
                me->toggleOn = 0;
                printf("ButtonDriver: Turning microwave OFF\n");
                Button_backlight(me->itsButton, 0);
                MicrowaveEmitter_stopEmitting(me->itsMicrowaveEmitter);
            } else {
                /* Toggle ON */
                me->toggleOn = 1;
                printf("ButtonDriver: Turning microwave ON\n");
                Button_backlight(me->itsButton, 1);
                MicrowaveEmitter_startEmitting(me->itsMicrowaveEmitter);
            }
        } else {
            /* Button press event - we ignore this for toggle functionality */
            printf("ButtonDriver: Button pressed - ignoring (waiting for release)\n");
        }
    } else {
        printf("ButtonDriver: False event detected (bouncing) - ignoring\n");
    }
}

struct Button* ButtonDriver_getItsButton(const ButtonDriver* const me) {
    return (struct Button*)me->itsButton;
}

void ButtonDriver_setItsButton(ButtonDriver* const me, struct Button* p_Button) {
    if (p_Button != NULL) {
        Button__setItsButtonDriver(p_Button, me);
    }
    ButtonDriver__setItsButton(me, p_Button);
}

struct MicrowaveEmitter* ButtonDriver_getItsMicrowaveEmitter(const ButtonDriver* const me) {
    return (struct MicrowaveEmitter*)me->itsMicrowaveEmitter;
}

void ButtonDriver_setItsMicrowaveEmitter(ButtonDriver* const me, struct MicrowaveEmitter* p_MicrowaveEmitter) {
    me->itsMicrowaveEmitter = p_MicrowaveEmitter;
}

struct Timer* ButtonDriver_getItsTimer(const ButtonDriver* const me) {
    return (struct Timer*)me->itsTimer;
}

void ButtonDriver_setItsTimer(ButtonDriver* const me, struct Timer* p_Timer) {
    me->itsTimer = p_Timer;
}

static void cleanUpRelations(ButtonDriver* const me) {
    if (me->itsButton != NULL) {
        Button__clearItsButtonDriver(me->itsButton);
        me->itsButton = NULL;
    }
    if (me->itsMicrowaveEmitter != NULL) {
        me->itsMicrowaveEmitter = NULL;
    }
    if (me->itsTimer != NULL) {
        me->itsTimer = NULL;
    }
}

void ButtonDriver___setItsButton(ButtonDriver* const me, struct Button* p_Button) {
    me->itsButton = p_Button;
}

void ButtonDriver__setItsButton(ButtonDriver* const me, struct Button* p_Button) {
    if (me->itsButton != NULL) {
        Button__clearItsButtonDriver(me->itsButton);
    }
    ButtonDriver___setItsButton(me, p_Button);
}

void ButtonDriver__clearItsButton(ButtonDriver* const me) {
    me->itsButton = NULL;
}
