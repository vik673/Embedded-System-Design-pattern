#include "AttitudeSensor.h"
#include "Mutex.h"
#include "ResourceList.h"
#include <stdlib.h>

static void cleanUpRelations(AttitudeSensor* const me);

void AttitudeSensor_Init(AttitudeSensor* const me) {
    me->resourceID = 3;  /* Highest ID for proper ordering */
    Attitude_Init(&(me->attitude));
    me->itsMutex = NULL;
    me->itsResourceList = NULL;
}

void AttitudeSensor_Cleanup(AttitudeSensor* const me) {
    cleanUpRelations(me);
}

struct Attitude AttitudeSensor_getAttitude(AttitudeSensor* const me) {
    return me->attitude;
}

int AttitudeSensor_lockDyadic(AttitudeSensor* const me) {
    int ok;
    
    Mutex_lock(me->itsMutex);
    ok = ResourceList_addLock(me->itsResourceList, me->resourceID);
    
    if (ok != 0) {
        Mutex_release(me->itsMutex);
    }
    
    return ok;
}

void AttitudeSensor_releaseDyadic(AttitudeSensor* const me) {
    ResourceList_removeLock(me->itsResourceList, me->resourceID);
    Mutex_release(me->itsMutex);
}

void AttitudeSensor_setAttitude(AttitudeSensor* const me, struct Attitude a) {
    me->attitude = a;
}

struct Mutex* AttitudeSensor_getItsMutex(const AttitudeSensor* const me) {
    return (struct Mutex*)me->itsMutex;
}

void AttitudeSensor_setItsMutex(AttitudeSensor* const me, struct Mutex* p_Mutex) {
    me->itsMutex = p_Mutex;
}

struct ResourceList* AttitudeSensor_getItsResourceList(const AttitudeSensor* const me) {
    return (struct ResourceList*)me->itsResourceList;
}

void AttitudeSensor_setItsResourceList(AttitudeSensor* const me, struct ResourceList* p_ResourceList) {
    me->itsResourceList = p_ResourceList;
}

AttitudeSensor* AttitudeSensor_Create(void) {
    AttitudeSensor* me = (AttitudeSensor*)malloc(sizeof(AttitudeSensor));
    if (me != NULL) {
        AttitudeSensor_Init(me);
    }
    return me;
}

void AttitudeSensor_Destroy(AttitudeSensor* const me) {
    if (me != NULL) {
        AttitudeSensor_Cleanup(me);
        free(me);
    }
}

static void cleanUpRelations(AttitudeSensor* const me) {
    if (me->itsMutex != NULL) {
        me->itsMutex = NULL;
    }
    
    if (me->itsResourceList != NULL) {
        me->itsResourceList = NULL;
    }
}
