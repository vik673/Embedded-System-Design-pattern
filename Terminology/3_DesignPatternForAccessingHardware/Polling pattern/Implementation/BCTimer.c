#include "BCTimer.h"
#include "BCPeriodicPoller.h"
#include <stdlib.h>
#include <stdio.h>

/* Simulated interrupt vector table entry */
static BCTimer* g_activeTimer = NULL;

/* Simulated hardware timer interrupt - in real embedded system this would be an ISR */
void BCTimer_handleTimerInterrupt(BCTimer* const me) {
    if (me != NULL && me->isRunning && me->itsBCPeriodicPoller != NULL) {
        /* Reset timer for next period (simulated) */
        printf("Timer interrupt fired - calling poll function\n");
        
        /* Call the poll function of the associated periodic poller */
        BCPeriodicPoller_poll(me->itsBCPeriodicPoller);
    }
}

void BCTimer_Init(BCTimer* const me) {
    if (me != NULL) {
        me->timerPeriod = 0;
        me->isRunning = 0;
        me->itsBCPeriodicPoller = NULL;
    }
}

void BCTimer_Cleanup(BCTimer* const me) {
    if (me != NULL) {
        BCTimer_stopTimer(me);
        BCTimer_removeInterruptHandler(me);
        me->itsBCPeriodicPoller = NULL;
    }
}

BCTimer* BCTimer_Create(void) {
    BCTimer* me = (BCTimer*)malloc(sizeof(BCTimer));
    if (me != NULL) {
        BCTimer_Init(me);
    }
    return me;
}

void BCTimer_Destroy(BCTimer* const me) {
    if (me != NULL) {
        BCTimer_Cleanup(me);
        free(me);
    }
}

void BCTimer_startTimer(BCTimer* const me, unsigned long period) {
    if (me != NULL) {
        me->timerPeriod = period;
        me->isRunning = 1;
        g_activeTimer = me;
        printf("Timer started with period: %lu ms\n", period);
    }
}

void BCTimer_stopTimer(BCTimer* const me) {
    if (me != NULL) {
        me->isRunning = 0;
        if (g_activeTimer == me) {
            g_activeTimer = NULL;
        }
        printf("Timer stopped\n");
    }
}

void BCTimer_installInterruptHandler(BCTimer* const me) {
    if (me != NULL) {
        /* In a real embedded system, this would install the ISR in the interrupt vector table */
        printf("Interrupt handler installed for timer\n");
    }
}

void BCTimer_removeInterruptHandler(BCTimer* const me) {
    if (me != NULL) {
        /* In a real embedded system, this would restore the original interrupt vector */
        printf("Interrupt handler removed for timer\n");
    }
}

struct BCPeriodicPoller* BCTimer_getItsBCPeriodicPoller(const BCTimer* const me) {
    if (me != NULL) {
        return me->itsBCPeriodicPoller;
    }
    return NULL;
}

void BCTimer_setItsBCPeriodicPoller(BCTimer* const me, struct BCPeriodicPoller* p_BCPeriodicPoller) {
    if (me != NULL) {
        me->itsBCPeriodicPoller = p_BCPeriodicPoller;
    }
}

void BCTimer___setItsBCPeriodicPoller(BCTimer* const me, struct BCPeriodicPoller* p_BCPeriodicPoller) {
    if (me != NULL) {
        me->itsBCPeriodicPoller = p_BCPeriodicPoller;
    }
}

void BCTimer__setItsBCPeriodicPoller(BCTimer* const me, struct BCPeriodicPoller* p_BCPeriodicPoller) {
    BCTimer___setItsBCPeriodicPoller(me, p_BCPeriodicPoller);
}

/* Simulation function to trigger timer interrupts periodically */
void BCTimer_simulateTimerTick(void) {
    if (g_activeTimer != NULL && g_activeTimer->isRunning) {
        BCTimer_handleTimerInterrupt(g_activeTimer);
    }
}
