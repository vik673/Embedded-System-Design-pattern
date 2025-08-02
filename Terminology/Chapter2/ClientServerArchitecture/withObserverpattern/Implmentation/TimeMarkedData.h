#ifndef TimeMarkedData_H
#define TimeMarkedData_H

#include "ECGPkg.h"

struct TMDQueue;

typedef struct TimeMarkedData TimeMarkedData;

struct TimeMarkedData {
    long timeInterval;
    int dataValue;
    struct TMDQueue* itsTMDQueue;
};

/* Constructors and destructors */
void TimeMarkedData_Init(TimeMarkedData* const me);
void TimeMarkedData_Cleanup(TimeMarkedData* const me);

/* Operations */
struct TMDQueue* TimeMarkedData_getItsTMDQueue(const TimeMarkedData* const me);
void TimeMarkedData__setItsTMDQueue(TimeMarkedData* const me, struct TMDQueue* p_TMDQueue);

TimeMarkedData* TimeMarkedData_Create(void);
void TimeMarkedData_Destroy(TimeMarkedData* const me);

#endif
