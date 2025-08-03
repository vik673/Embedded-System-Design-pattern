#include "ECG_Module.h"
#include "TMDQueue.h"
#include "TimeMarkedData.h"

static void cleanUpRelations(ECG_Module* const me);

void ECG_Module_Init(ECG_Module* const me) {
    me->itsTMDQueue = NULL;
}

void ECG_Module_Cleanup(ECG_Module* const me) {
    cleanUpRelations(me);
}

void ECG_Module_getDataSample(ECG_Module* const me) {
    /* Simulate getting data from ECG hardware */
    static long timeCounter = 1000;
    static int dataCounter = 100;
    
    TimeMarkedData tmd;
    tmd.timeInterval = timeCounter++;
    tmd.dataValue = dataCounter++;
    
    /* Insert data into the queue, which will notify all observers */
    TMDQueue_insert(me->itsTMDQueue, tmd);
}

struct TMDQueue* ECG_Module_getItsTMDQueue(const ECG_Module* const me) {
    return (struct TMDQueue*)me->itsTMDQueue;
}

void ECG_Module_setItsTMDQueue(ECG_Module* const me, struct TMDQueue* p_TMDQueue) {
    me->itsTMDQueue = p_TMDQueue;
}

ECG_Module* ECG_Module_Create(void) {
    ECG_Module* me = (ECG_Module*)malloc(sizeof(ECG_Module));
    if (me != NULL) {
        ECG_Module_Init(me);
    }
    return me;
}

void ECG_Module_Destroy(ECG_Module* const me) {
    if (me != NULL) {
        ECG_Module_Cleanup(me);
    }
    free(me);
}

static void cleanUpRelations(ECG_Module* const me) {
    if (me->itsTMDQueue != NULL) {
        me->itsTMDQueue = NULL;
    }
}
