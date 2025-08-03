#ifndef POSITION_SENSOR_H
#define POSITION_SENSOR_H

#include "OrderedLockingExample.h"
#include "Position.h"

struct Mutex;
struct ResourceList;

typedef struct PositionSensor PositionSensor;

struct PositionSensor {
    int resourceID;
    struct Position position;
    struct Mutex* itsMutex;
    struct ResourceList* itsResourceList;
};

void PositionSensor_Init(PositionSensor* const me);
void PositionSensor_Cleanup(PositionSensor* const me);

/* Operations */
struct Position PositionSensor_getPosition(PositionSensor* const me);
int PositionSensor_lockDyadic(PositionSensor* const me);
void PositionSensor_releaseDyadic(PositionSensor* const me);
void PositionSensor_setPosition(PositionSensor* const me, struct Position p);

struct Mutex* PositionSensor_getItsMutex(const PositionSensor* const me);
void PositionSensor_setItsMutex(PositionSensor* const me, struct Mutex* p_Mutex);

struct ResourceList* PositionSensor_getItsResourceList(const PositionSensor* const me);
void PositionSensor_setItsResourceList(PositionSensor* const me, struct ResourceList* p_ResourceList);

PositionSensor* PositionSensor_Create(void);
void PositionSensor_Destroy(PositionSensor* const me);

#endif /* POSITION_SENSOR_H */
