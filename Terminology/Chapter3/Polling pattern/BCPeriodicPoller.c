#include "BCPeriodicPoller.h"
#include "BCTimer.h"
#include "BreathingCircuitSensor.h"
#include "MedicalDisplay.h"
#include <stdlib.h>
#include <stdio.h>

static void cleanUpRelations(BCPeriodicPoller* const me);

void BCPeriodicPoller_Init(BCPeriodicPoller* const me) {
    if (me != NULL) {
        me->pollTime = DEFAULT_POLL_TIME;
        me->itsBCTimer = NULL;
        
        int pos;
        for(pos = 0; pos < 3; ++pos) {
            me->itsBreathingCircuitSensor[pos] = NULL;
        }
        me->itsMedicalDisplay = NULL;
        
        /* Note: Timer interrupt handler installation is done when timer is created */
        printf("BCPeriodicPoller initialized\n");
    }
}

void BCPeriodicPoller_Cleanup(BCPeriodicPoller* const me) {
    if (me != NULL) {
        if (me->itsBCTimer != NULL) {
            BCTimer_stopTimer(me->itsBCTimer);
            BCTimer_removeInterruptHandler(me->itsBCTimer);
        }
        
        cleanUpRelations(me);
        printf("BCPeriodicPoller cleanup completed\n");
    }
}

void BCPeriodicPoller_poll(BCPeriodicPoller* const me) {
    if (me != NULL && me->itsMedicalDisplay != NULL) {
        int state, data;
        
        printf("--- Polling sensors ---\n");
        
        /* Poll O2 concentration sensor */
        if (me->itsBreathingCircuitSensor[0] != NULL) {
            /* Simulate new sensor reading */
            BreathingCircuitSensor_simulateReading(me->itsBreathingCircuitSensor[0]);
            data = BreathingCircuitSensor_getData(me->itsBreathingCircuitSensor[0]);
            MedicalDisplay_showO2Concentration(me->itsMedicalDisplay, data);
        }
        
        /* Poll gas pressure sensor */
        if (me->itsBreathingCircuitSensor[1] != NULL) {
            /* Simulate new sensor reading */
            BreathingCircuitSensor_simulateReading(me->itsBreathingCircuitSensor[1]);
            data = BreathingCircuitSensor_getData(me->itsBreathingCircuitSensor[1]);
            state = BreathingCircuitSensor_getState(me->itsBreathingCircuitSensor[1]);
            MedicalDisplay_showGasFlow(me->itsMedicalDisplay, data);
            MedicalDisplay_showGasFlowStatus(me->itsMedicalDisplay, state);
        }
        
        /* Poll circuit pressure sensor */
        if (me->itsBreathingCircuitSensor[2] != NULL) {
            /* Simulate new sensor reading */
            BreathingCircuitSensor_simulateReading(me->itsBreathingCircuitSensor[2]);
            data = BreathingCircuitSensor_getData(me->itsBreathingCircuitSensor[2]);
            MedicalDisplay_showCircuitPressure(me->itsMedicalDisplay, data);
        }
        
        printf("--- End polling ---\n\n");
    }
}

void BCPeriodicPoller_setPollTime(BCPeriodicPoller* const me, unsigned long t) {
    if (me != NULL) {
        me->pollTime = t;
        printf("Poll time set to: %lu ms\n", t);
    }
}

void BCPeriodicPoller_startPolling(BCPeriodicPoller* const me) {
    if (me != NULL && me->itsBCTimer != NULL) {
        BCTimer_startTimer(me->itsBCTimer, me->pollTime);
        printf("Periodic polling started\n");
    }
}

void BCPeriodicPoller_stopPolling(BCPeriodicPoller* const me) {
    if (me != NULL && me->itsBCTimer != NULL) {
        BCTimer_stopTimer(me->itsBCTimer);
        printf("Periodic polling stopped\n");
    }
}

struct BCTimer* BCPeriodicPoller_getItsBCTimer(const BCPeriodicPoller* const me) {
    if (me != NULL) {
        return (struct BCTimer*)me->itsBCTimer;
    }
    return NULL;
}

void BCPeriodicPoller_setItsBCTimer(BCPeriodicPoller* const me, struct BCTimer* p_BCTimer) {
    if (me != NULL) {
        if(p_BCTimer != NULL) {
            BCTimer__setItsBCPeriodicPoller(p_BCTimer, me);
        }
        BCPeriodicPoller__setItsBCTimer(me, p_BCTimer);
    }
}

int BCPeriodicPoller_getItsBreathingCircuitSensor(const BCPeriodicPoller* const me) {
    int count = 0;
    if (me != NULL) {
        int pos;
        for(pos = 0; pos < 3; ++pos) {
            if (me->itsBreathingCircuitSensor[pos] != NULL) {
                count++;
            }
        }
    }
    return count;
}

void BCPeriodicPoller_addItsBreathingCircuitSensor(BCPeriodicPoller* const me, struct BreathingCircuitSensor * p_BreathingCircuitSensor) {
    if (me != NULL && p_BreathingCircuitSensor != NULL) {
        int pos;
        for(pos = 0; pos < 3; ++pos) {
            if (me->itsBreathingCircuitSensor[pos] == NULL) {
                me->itsBreathingCircuitSensor[pos] = p_BreathingCircuitSensor;
                printf("Breathing circuit sensor added at position %d\n", pos);
                break;
            }
        }
    }
}

void BCPeriodicPoller_removeItsBreathingCircuitSensor(BCPeriodicPoller* const me, struct BreathingCircuitSensor * p_BreathingCircuitSensor) {
    if (me != NULL && p_BreathingCircuitSensor != NULL) {
        int pos;
        for(pos = 0; pos < 3; ++pos) {
            if (me->itsBreathingCircuitSensor[pos] == p_BreathingCircuitSensor) {
                me->itsBreathingCircuitSensor[pos] = NULL;
                printf("Breathing circuit sensor removed from position %d\n", pos);
                break;
            }
        }
    }
}

void BCPeriodicPoller_clearItsBreathingCircuitSensor(BCPeriodicPoller* const me) {
    if (me != NULL) {
        int pos;
        for(pos = 0; pos < 3; ++pos) {
            me->itsBreathingCircuitSensor[pos] = NULL;
        }
        printf("All breathing circuit sensors cleared\n");
    }
}

struct MedicalDisplay* BCPeriodicPoller_getItsMedicalDisplay(const BCPeriodicPoller* const me) {
    if (me != NULL) {
        return (struct MedicalDisplay*)me->itsMedicalDisplay;
    }
    return NULL;
}

void BCPeriodicPoller_setItsMedicalDisplay(BCPeriodicPoller* const me, struct MedicalDisplay* p_MedicalDisplay) {
    if (me != NULL) {
        me->itsMedicalDisplay = p_MedicalDisplay;
        printf("Medical display connected to periodic poller\n");
    }
}

BCPeriodicPoller * BCPeriodicPoller_Create(void) {
    BCPeriodicPoller* me = (BCPeriodicPoller *)malloc(sizeof(BCPeriodicPoller));
    if(me != NULL) {
        BCPeriodicPoller_Init(me);
    }
    return me;
}

void BCPeriodicPoller_Destroy(BCPeriodicPoller* const me) {
    if(me != NULL) {
        BCPeriodicPoller_Cleanup(me);
        free(me);
    }
}

static void cleanUpRelations(BCPeriodicPoller* const me) {
    if (me != NULL) {
        if(me->itsBCTimer != NULL) {
            struct BCPeriodicPoller* p_BCPeriodicPoller = BCTimer_getItsBCPeriodicPoller(me->itsBCTimer);
            if(p_BCPeriodicPoller != NULL) {
                BCTimer___setItsBCPeriodicPoller(me->itsBCTimer, NULL);
            }
            me->itsBCTimer = NULL;
        }
        
        if(me->itsMedicalDisplay != NULL) {
            me->itsMedicalDisplay = NULL;
        }
        
        /* Clear all sensor references */
        int pos;
        for(pos = 0; pos < 3; ++pos) {
            me->itsBreathingCircuitSensor[pos] = NULL;
        }
    }
}

void BCPeriodicPoller___setItsBCTimer(BCPeriodicPoller* const me, struct BCTimer* p_BCTimer) {
    if (me != NULL) {
        me->itsBCTimer = p_BCTimer;
    }
}

void BCPeriodicPoller__setItsBCTimer(BCPeriodicPoller* const me, struct BCTimer* p_BCTimer) {
    if (me != NULL) {
        if(me->itsBCTimer != NULL) {
            BCTimer___setItsBCPeriodicPoller(me->itsBCTimer, NULL);
        }
        BCPeriodicPoller___setItsBCTimer(me, p_BCTimer);
    }
}

void BCPeriodicPoller__clearItsBCTimer(BCPeriodicPoller* const me) {
    if (me != NULL) {
        me->itsBCTimer = NULL;
    }
}
