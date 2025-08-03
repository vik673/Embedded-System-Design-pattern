#ifndef BCTimer_H
#define BCTimer_H

struct BCPeriodicPoller;

typedef struct BCTimer BCTimer;
struct BCTimer {
    unsigned long timerPeriod;
    int isRunning;
    struct BCPeriodicPoller* itsBCPeriodicPoller;
};

/* Constructor and Destructor */
void BCTimer_Init(BCTimer* const me);
void BCTimer_Cleanup(BCTimer* const me);
BCTimer* BCTimer_Create(void);
void BCTimer_Destroy(BCTimer* const me);

/* Operations */
void BCTimer_startTimer(BCTimer* const me, unsigned long period);
void BCTimer_stopTimer(BCTimer* const me);
void BCTimer_handleTimerInterrupt(BCTimer* const me);
void BCTimer_installInterruptHandler(BCTimer* const me);
void BCTimer_removeInterruptHandler(BCTimer* const me);

/* Relationship management */
struct BCPeriodicPoller* BCTimer_getItsBCPeriodicPoller(const BCTimer* const me);
void BCTimer_setItsBCPeriodicPoller(BCTimer* const me, struct BCPeriodicPoller* p_BCPeriodicPoller);
void BCTimer___setItsBCPeriodicPoller(BCTimer* const me, struct BCPeriodicPoller* p_BCPeriodicPoller);
void BCTimer__setItsBCPeriodicPoller(BCTimer* const me, struct BCPeriodicPoller* p_BCPeriodicPoller);

#endif
