#include "Sensor.h"
#include <stdlib.h>
#include <stddef.h>
#define MEMORYMAPPED 1
#define PORTMAPPED 2
#define WRITEMASK 0x01 /* Example command to force a read */

void Sensor_Init(Sensor* const me) {
    me->filterFrequency = 0;
    me->updateFrequency = 0;
    me->value = 0;
}

void Sensor_Cleanup(Sensor* const me) {
    // Cleanup logic if needed
    // Currently, there is no dynamic memory to free in this struct
}

int Sensor_getFilterFrequency(const Sensor* const me) {

   return me->filterFrequency;
}

int acquireValue(Sensor *me) {
int *r, *w; /* read and write addresses */
int j;
switch(me->whatKindOfInterface) {
case  MEMORYMAPPED:
    w=(int*) me->WRITEADDR; /* address to write to sensor */
    *w = WRITEMASK; /* sensor command to force a read */
    for (j=0;j<100;j++) { /* wait loop */ };
    r=(int *) me->READADDR; /* address of returned value */
    me->value = *r;
    break;
case PORTMAPPED:
    me->value = me->SENSORPORT;
    /* inp() is a compiler-specific port function */
    break;
}; /* end switch */
return me->value;
};

void Sensor_setFilterFrequency(Sensor* const me, int p_filterFrequency) {
     me->filterFrequency = p_filterFrequency;
}

int Sensor_getUpdateFrequency(const Sensor* const me) {
   return me->updateFrequency;
}

void Sensor_setUpdateFrequency(Sensor* const me, int p_updateFrequency) {
    me->updateFrequency = p_updateFrequency;
}

int Sensor_getValue(const Sensor* const me) {
    return me->value;
}

Sensor * Sensor_Create(void) {
    Sensor* me = (Sensor *) malloc(sizeof(Sensor));
    if(me!= NULL)
    {
        Sensor_Init(me);
    }
    return me;
}

void Sensor_Destroy(Sensor* const me) {
    if(me!=NULL)
    {
        Sensor_Cleanup(me);
    }
    free(me);
}