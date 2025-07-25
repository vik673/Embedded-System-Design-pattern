#include "PositionSensor.h"
#include "Mutex.h"
#include "ResourceList.h"
#include <stdlib.h>

static void cleanUpRelations(PositionSensor* const me);

void PositionSensor_Init(PositionSensor* const me) {
    me->resourceID = 1;  /* Lowest ID for proper ordering */
    Position_Init(&(me->position));
    me->itsMutex = NULL;
    me->itsResourceList = NULL;
}

void PositionSensor_Cleanup(PositionSensor* const me) {
    cleanUpRelations(me);
}

struct Position PositionSensor_getPosition(PositionSensor* const me) {
    return me->position;
}

int PositionSensor_lockDyadic(PositionSensor* const me) {
    int ok;
    
    Mutex_lock(me->itsMutex);
    ok = ResourceList_addLock(me->itsResourceList, me->resourceID);
    
    if (ok != 0) {
        Mutex_release(me->itsMutex);
    }
    
    return ok;
}

void PositionSensor_releaseDyadic(PositionSensor* const me) {
    ResourceList_removeLock(me->itsResourceList, me->resourceID);
    Mutex_release(me->itsMutex);
}

void PositionSensor_setPosition(PositionSensor* const me, struct Position p) {
    me->position = p;
}

struct Mutex* PositionSensor_getItsMutex(const PositionSensor* const me) {
    return (struct Mutex*)me->itsMutex;
}

void PositionSensor_setItsMutex(PositionSensor* const me, struct Mutex* p_Mutex) {
    me->itsMutex = p_Mutex;
}

struct ResourceList* PositionSensor_getItsResourceList(const PositionSensor* const me) {
    return (struct ResourceList*)me->itsResourceList;
}

void PositionSensor_setItsResourceList(PositionSensor* const me, struct ResourceList* p_ResourceList) {
    me->itsResourceList = p_ResourceList;
}

PositionSensor* PositionSensor_Create(void) {
    PositionSensor* me = (PositionSensor*)malloc(sizeof(PositionSensor));
    if (me != NULL) {
        PositionSensor_Init(me);
    }
    return me;
}

void PositionSensor_Destroy(PositionSensor* const me) {
    if (me != NULL) {
        PositionSensor_Cleanup(me);
        free(me);
    }
}

static void cleanUpRelations(PositionSensor* const me) {
    if (me->itsMutex != NULL) {
        me->itsMutex = NULL;
    }
    
    if (me->itsResourceList != NULL) {
        me->itsResourceList = NULL;
    }
}
