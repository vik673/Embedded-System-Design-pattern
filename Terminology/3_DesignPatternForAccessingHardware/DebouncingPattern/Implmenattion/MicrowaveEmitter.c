#include "MicrowaveEmitter.h"
#include <stdlib.h>
#include <stdio.h>

void MicrowaveEmitter_Init(MicrowaveEmitter* const me) {
    me->isEmitting = 0;  /* Initially off */
    me->powerLevel = 50; /* Default 50% power */
}

void MicrowaveEmitter_Cleanup(MicrowaveEmitter* const me) {
    /* Ensure emitter is turned off during cleanup */
    if (me->isEmitting) {
        MicrowaveEmitter_stopEmitting(me);
    }
}

MicrowaveEmitter* MicrowaveEmitter_Create(void) {
    MicrowaveEmitter* me = (MicrowaveEmitter*)malloc(sizeof(MicrowaveEmitter));
    if (me != NULL) {
        MicrowaveEmitter_Init(me);
    }
    return me;
}

void MicrowaveEmitter_Destroy(MicrowaveEmitter* const me) {
    if (me != NULL) {
        MicrowaveEmitter_Cleanup(me);
        free(me);
    }
}

void MicrowaveEmitter_startEmitting(MicrowaveEmitter* const me) {
    if (!me->isEmitting) {
        me->isEmitting = 1;
        printf("*** MICROWAVE EMITTER STARTED *** (Power: %u%%)\n", me->powerLevel);
        printf("    Microwave is now heating...\n");
    } else {
        printf("Microwave emitter is already running\n");
    }
}

void MicrowaveEmitter_stopEmitting(MicrowaveEmitter* const me) {
    if (me->isEmitting) {
        me->isEmitting = 0;
        printf("*** MICROWAVE EMITTER STOPPED ***\n");
        printf("    Microwave has stopped heating\n");
    } else {
        printf("Microwave emitter is already stopped\n");
    }
}

unsigned char MicrowaveEmitter_isEmittingMicrowaves(const MicrowaveEmitter* const me) {
    return me->isEmitting;
}

void MicrowaveEmitter_setPowerLevel(MicrowaveEmitter* const me, unsigned int power) {
    if (power > 100) {
        power = 100;  /* Cap at 100% */
    }
    
    me->powerLevel = power;
    printf("Microwave power level set to %u%%\n", power);
    
    if (me->isEmitting) {
        printf("Power level changed while emitting - new power: %u%%\n", power);
    }
}

unsigned int MicrowaveEmitter_getPowerLevel(const MicrowaveEmitter* const me) {
    return me->powerLevel;
}
