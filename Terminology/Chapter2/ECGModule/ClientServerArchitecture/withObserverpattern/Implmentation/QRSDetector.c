#include "QRSDetector.h"
#include "TimeMarkedData.h"
#include "TMDQueue.h"

static void cleanUpRelations(QRSDetector* const me);

void QRSDetector_Init(QRSDetector* const me) {
    me->itsTMDQueue = NULL;
}

void QRSDetector_Cleanup(QRSDetector* const me) {
    /* remove yourself from server subscription list */
    if (me->itsTMDQueue != NULL) {
        TMDQueue_unsubscribe(me->itsTMDQueue, QRSDetector_update);
    }
    cleanUpRelations(me);
}

void QRSDetector_update(QRSDetector* const me, const struct TimeMarkedData tmd) {
    printf(" QRS Detector -> TimeInterval: %ld DataValue: %d\n", tmd.timeInterval, tmd.dataValue);
}

void QRSDetector_detectQRS(QRSDetector* const me) {
    /* put some QRS detection algorithm here */
}

struct TMDQueue* QRSDetector_getItsTMDQueue(const QRSDetector* const me) {
    return (struct TMDQueue*)me->itsTMDQueue;
}

void QRSDetector_setItsTMDQueue(QRSDetector* const me, struct TMDQueue* p_TMDQueue) {
    me->itsTMDQueue = p_TMDQueue;
    /* call subscribe to connect to the server */
    if (p_TMDQueue != NULL) {
        TMDQueue_subscribe(me->itsTMDQueue, QRSDetector_update);
    }
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
