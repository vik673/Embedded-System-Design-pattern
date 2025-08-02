#include "SensorThread.h"
#include <stdlib.h>
#include <stdio.h>

static void cleanUpRelations(SensorThread* const me);
static void initRelations(SensorThread* const me);

void SensorThread_Init(SensorThread* const me) {
    me->itsGasDataQueue = NULL;
    initRelations(me);
}

void SensorThread_Cleanup(SensorThread* const me) {
    cleanUpRelations(me);
}

/*
updateData runs every period of the sensor thread
and calls the getXXData() function of each of
its sensors, then uses a random number generator
to decide which data should be published to the
GasDataQueue.
*/
void SensorThread_updateData(SensorThread* const me) {
    unsigned char success;
    GasData g;

    GasData_Init(&g);

    O2Sensor_getO2Data(&(me->itsO2Sensor));
    N2Sensor_getN2Data(&(me->itsN2Sensor));
    HeSensor_getHeData(&(me->itsHeSensor));

    if (rand() > RAND_MAX / 3) {
        g.gType = HE_GAS;
        g.conc = me->itsHeSensor.conc;
        g.flowInCCPerMin = me->itsHeSensor.flow;

        success = GasDataQueue_insert(me->itsGasDataQueue, g);
        if (!success)
            printf("Helium Gas Data queue insertion failed!\n");
    };

    if (rand() > RAND_MAX / 3) {
        g.gType = N2_GAS;
        g.conc = me->itsN2Sensor.conc;
        g.flowInCCPerMin = me->itsN2Sensor.flow;

        success = GasDataQueue_insert(me->itsGasDataQueue, g);
        if (!success)
            printf("Nitrogen Gas Data queue insertion failed!\n");
    };

    if (rand() > RAND_MAX / 3) {
        g.gType = O2_GAS;
        g.conc = me->itsO2Sensor.conc;
        g.flowInCCPerMin = me->itsO2Sensor.flow;

        success = GasDataQueue_insert(me->itsGasDataQueue, g);
        if (!success)
            printf("Oxygen Gas Data queue insertion failed! \n");
    }
}

struct GasDataQueue* SensorThread_getItsGasDataQueue(const SensorThread* const me) {
    return (struct GasDataQueue*)me->itsGasDataQueue;
}

void SensorThread_setItsGasDataQueue(SensorThread* const me, struct GasDataQueue* p_GasDataQueue) {
    me->itsGasDataQueue = p_GasDataQueue;
}

SensorThread* SensorThread_Create(void) {
    SensorThread* me = (SensorThread*)malloc(sizeof(SensorThread));
    if (me != NULL) {
        SensorThread_Init(me);
    }
    return me;
}

void SensorThread_Destroy(SensorThread* const me) {
    if (me != NULL) {
        SensorThread_Cleanup(me);
    }
    free(me);
}

static void initRelations(SensorThread* const me) {
    O2Sensor_Init(&(me->itsO2Sensor));
    N2Sensor_Init(&(me->itsN2Sensor));
    HeSensor_Init(&(me->itsHeSensor));
}

static void cleanUpRelations(SensorThread* const me) {
    O2Sensor_Cleanup(&(me->itsO2Sensor));
    N2Sensor_Cleanup(&(me->itsN2Sensor));
    HeSensor_Cleanup(&(me->itsHeSensor));
}
