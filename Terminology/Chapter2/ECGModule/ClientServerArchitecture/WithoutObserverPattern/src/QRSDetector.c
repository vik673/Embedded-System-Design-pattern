#include "QRSDetector.h"
#include "TMDQueue.h"

static void cleanUpRelations(QRSDetector* const me);

void QRSDetector_Init(QRSDetector* const me) {
    me->index = 0;
    me->itsTMDQueue = NULL;
}

void QRSDetector_Cleanup(QRSDetector* const me) {
    cleanUpRelations(me);
}

/* operation getDataSample() */
void QRSDetector_getDataSample(QRSDetector* const me) {
    TimeMarkedData tmd;
    tmd = TMDQueue_remove(me->itsTMDQueue, me->index);
    printf(" QRS index: %d TimeInterval: %ld DataValue: %d\n", 
           me->index, tmd.timeInterval, tmd.dataValue);
    me->index = TMDQueue_getNextIndex(me->itsTMDQueue, me->index);
}

/* operation detectQRS() */
void QRSDetector_detectQRS(QRSDetector* const me) {
    /* put some QRS detection algorithm here… */
}

struct TMDQueue* QRSDetector_getItsTMDQueue(const QRSDetector* const me) {
    return (struct TMDQueue*)me->itsTMDQueue;
}

void QRSDetector_setItsTMDQueue(QRSDetector* const me, struct TMDQueue* p_TMDQueue) {
    me->itsTMDQueue = p_TMDQueue;
}

QRSDetector* QRSDetector_Create(void) {
    QRSDetector* me = (QRSDetector*)malloc(sizeof(QRSDetector));
    if (me != NULL) {
        QRSDetector_Init(me);
    }
    return me;
}

void QRSDetector_Destroy(QRSDetector* const me) {
    if (me != NULL) {
        QRSDetector_Cleanup(me);
    }
    free(me);
}

static void cleanUpRelations(QRSDetector* const me) {
    if (me->itsTMDQueue != NULL) {
        me->itsTMDQueue = NULL;
    }
}
