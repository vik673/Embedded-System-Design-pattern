#include "TimeMarkedData.h"
#include "TMDQueue.h"

static void cleanUpRelations(TimeMarkedData* const me);

void TimeMarkedData_Init(TimeMarkedData* const me) {
    me->timeInterval = 0;
    me->dataValue = 0;
    me->itsTMDQueue = NULL;
}

void TimeMarkedData_Cleanup(TimeMarkedData* const me) {
    cleanUpRelations(me);
}

struct TMDQueue* TimeMarkedData_getItsTMDQueue(const TimeMarkedData* const me) {
    return (struct TMDQueue*)me->itsTMDQueue;
}

void TimeMarkedData__setItsTMDQueue(TimeMarkedData* const me, struct TMDQueue* p_TMDQueue) {
    me->itsTMDQueue = p_TMDQueue;
}

TimeMarkedData* TimeMarkedData_Create(void) {
    TimeMarkedData* me = (TimeMarkedData*)malloc(sizeof(TimeMarkedData));
    if (me != NULL) {
        TimeMarkedData_Init(me);
    }
    return me;
}

void TimeMarkedData_Destroy(TimeMarkedData* const me) {
    if (me != NULL) {
        TimeMarkedData_Cleanup(me);
    }
    free(me);
}

static void cleanUpRelations(TimeMarkedData* const me) {
    if (me->itsTMDQueue != NULL) {
        me->itsTMDQueue = NULL;
    }
}
