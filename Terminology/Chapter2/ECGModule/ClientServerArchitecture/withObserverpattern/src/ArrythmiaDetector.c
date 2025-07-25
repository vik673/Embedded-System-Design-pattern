#include "ArrythmiaDetector.h"
#include "TimeMarkedData.h"
#include "TMDQueue.h"

static void cleanUpRelations(ArrythmiaDetector* const me);

void ArrythmiaDetector_Init(ArrythmiaDetector* const me) {
    me->itsTMDQueue = NULL;
}

void ArrythmiaDetector_Cleanup(ArrythmiaDetector* const me) {
    /* remove yourself from server subscription list */
    if (me->itsTMDQueue != NULL) {
        TMDQueue_unsubscribe(me->itsTMDQueue, ArrythmiaDetector_update);
    }
    cleanUpRelations(me);
}

void ArrythmiaDetector_update(ArrythmiaDetector* const me, const struct TimeMarkedData tmd) {
    printf(" Arrythmia Detector -> TimeInterval: %ld DataValue: %d\n", tmd.timeInterval, tmd.dataValue);
}

void ArrythmiaDetector_detectArrythmia(ArrythmiaDetector* const me) {
    /* put some arrythmia detection algorithm here */
}

struct TMDQueue* ArrythmiaDetector_getItsTMDQueue(const ArrythmiaDetector* const me) {
    return (struct TMDQueue*)me->itsTMDQueue;
}

void ArrythmiaDetector_setItsTMDQueue(ArrythmiaDetector* const me, struct TMDQueue* p_TMDQueue) {
    me->itsTMDQueue = p_TMDQueue;
    /* call subscribe to connect to the server */
    if (p_TMDQueue != NULL) {
        TMDQueue_subscribe(me->itsTMDQueue, ArrythmiaDetector_update);
    }
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
