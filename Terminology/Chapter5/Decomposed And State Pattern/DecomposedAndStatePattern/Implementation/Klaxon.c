#include "Klaxon.h"
#include <stdlib.h>
#include <stdio.h>

void Klaxon_Init(Klaxon* const me) {
    me->isAlarming = 0;
}

void Klaxon_Cleanup(Klaxon* const me) {
    // Nothing to cleanup for now
}

void Klaxon_alarmOn(Klaxon* const me) {
    me->isAlarming = 1;
    printf("Klaxon: ALARM ON! Emergency state activated!\n");
}

void Klaxon_alarmOff(Klaxon* const me) {
    me->isAlarming = 0;
    printf("Klaxon: Alarm OFF\n");
}

int Klaxon_isAlarming(const Klaxon* const me) {
    return me->isAlarming;
}

Klaxon * Klaxon_Create(void) {
    Klaxon* me = (Klaxon *)malloc(sizeof(Klaxon));
    if(me!=NULL)
        Klaxon_Init(me);
    return me;
}

void Klaxon_Destroy(Klaxon* const me) {
    if(me!=NULL)
        Klaxon_Cleanup(me);
    free(me);
}
