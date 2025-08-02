#ifndef ATTITUDE_SENSOR_H
#define ATTITUDE_SENSOR_H

#include "OrderedLockingExample.h"
#include "Attitude.h"

struct Mutex;
struct ResourceList;

typedef struct AttitudeSensor AttitudeSensor;

struct AttitudeSensor {
    int resourceID;
    struct Attitude attitude;
    struct Mutex* itsMutex;
    struct ResourceList* itsResourceList;
};

void AttitudeSensor_Init(AttitudeSensor* const me);
void AttitudeSensor_Cleanup(AttitudeSensor* const me);

/* Operations */
struct Attitude AttitudeSensor_getAttitude(AttitudeSensor* const me);
int AttitudeSensor_lockDyadic(AttitudeSensor* const me);
void AttitudeSensor_releaseDyadic(AttitudeSensor* const me);
void AttitudeSensor_setAttitude(AttitudeSensor* const me, struct Attitude a);

struct Mutex* AttitudeSensor_getItsMutex(const AttitudeSensor* const me);
void AttitudeSensor_setItsMutex(AttitudeSensor* const me, struct Mutex* p_Mutex);

struct ResourceList* AttitudeSensor_getItsResourceList(const AttitudeSensor* const me);
void AttitudeSensor_setItsResourceList(AttitudeSensor* const me, struct ResourceList* p_ResourceList);

AttitudeSensor* AttitudeSensor_Create(void);
void AttitudeSensor_Destroy(AttitudeSensor* const me);

#endif /* ATTITUDE_SENSOR_H */
