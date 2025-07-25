#include "ArrythmiaDetector.h"
#include "TMDQueue.h"

static void cleanUpRelations(ArrythmiaDetector* const me);

void ArrythmiaDetector_Init(ArrythmiaDetector* const me) {
    me->index = 0;
    me->itsTMDQueue = NULL;
}

void ArrythmiaDetector_Cleanup(ArrythmiaDetector* const me) {
    cleanUpRelations(me);
}

/* operation getDataSample() */
void ArrythmiaDetector_getDataSample(ArrythmiaDetector* const me) {
    TimeMarkedData tmd;
    tmd = TMDQueue_remove(me->itsTMDQueue, me->index);
    printf(" Arrythmia index: %d TimeInterval: %ld DataValue: %d\n", 
           me->index, tmd.timeInterval, tmd.dataValue);
    me->index = TMDQueue_getNextIndex(me->itsTMDQueue, me->index);
}

/* operation detectArrythmia() */
void ArrythmiaDetector_detectArrythmia(ArrythmiaDetector* const me) {
    /* put some arrythmia detection algorithm here… */
}

struct TMDQueue* ArrythmiaDetector_getItsTMDQueue(const ArrythmiaDetector* const me) {
    return (struct TMDQueue*)me->itsTMDQueue;
}

void ArrythmiaDetector_setItsTMDQueue(ArrythmiaDetector* const me, struct TMDQueue* p_TMDQueue) {
    me->itsTMDQueue = p_TMDQueue;
}

ArrythmiaDetector* ArrythmiaDetector_Create(void) {
    ArrythmiaDetector* me = (ArrythmiaDetector*)malloc(sizeof(ArrythmiaDetector));
    if (me != NULL) {
        ArrythmiaDetector_Init(me);
    }
    return me;
}

void ArrythmiaDetector_Destroy(ArrythmiaDetector* const me) {
    if (me != NULL) {
        ArrythmiaDetector_Cleanup(me);
    }
    free(me);
}

static void cleanUpRelations(ArrythmiaDetector* const me) {
    if (me->itsTMDQueue != NULL) {
        me->itsTMDQueue = NULL;
    }
}
