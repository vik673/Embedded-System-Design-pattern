#ifndef SensorThread_H
#define SensorThread_H

#include "QueuingExample.h"
#include "GasDataQueue.h"
#include "O2Sensor.h"
#include "N2Sensor.h"
#include "HeSensor.h"

typedef struct SensorThread SensorThread;
struct SensorThread {
    struct GasDataQueue* itsGasDataQueue;
    struct HeSensor itsHeSensor;
    struct N2Sensor itsN2Sensor;
    struct O2Sensor itsO2Sensor;
};

/* Constructors and destructors */
void SensorThread_Init(SensorThread* const me);
void SensorThread_Cleanup(SensorThread* const me);

/* Operations */
void SensorThread_updateData(SensorThread* const me);

/* Relations */
struct GasDataQueue* SensorThread_getItsGasDataQueue(const SensorThread* const me);
void SensorThread_setItsGasDataQueue(SensorThread* const me, struct GasDataQueue* p_GasDataQueue);

SensorThread* SensorThread_Create(void);
void SensorThread_Destroy(SensorThread* const me);

#endif
