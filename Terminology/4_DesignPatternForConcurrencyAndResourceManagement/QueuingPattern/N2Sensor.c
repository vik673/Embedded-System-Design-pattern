#include "N2Sensor.h"
#include <stdlib.h>
#include <stdio.h>

void N2Sensor_Init(N2Sensor* const me) {
    me->conc = 0.0;
    me->flow = 0;
}

void N2Sensor_Cleanup(N2Sensor* const me) {
    /* Nothing to cleanup */
}

/*
getN2Data() is where the sensor class would
actually acquire the data. Here it just
augments it.
*/
void N2Sensor_getN2Data(N2Sensor* const me) {
    me->conc += 30;
    me->flow += 35;
}

N2Sensor* N2Sensor_Create(void) {
    N2Sensor* me = (N2Sensor*)malloc(sizeof(N2Sensor));
    if (me != NULL) {
        N2Sensor_Init(me);
    }
    return me;
}

void N2Sensor_Destroy(N2Sensor* const me) {
    if (me != NULL) {
        N2Sensor_Cleanup(me);
    }
    free(me);
}
