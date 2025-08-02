#include "GasProcessingThread.h"
#include "GasDisplay.h"
#include <stdio.h>

static void cleanUpRelations(GasProcessingThread* const me);
static void initRelations(GasProcessingThread* const me);

void GasProcessingThread_Init(GasProcessingThread* const me) {
    me->itsGasDataQueue = NULL;
    initRelations(me);
}

void GasProcessingThread_Cleanup(GasProcessingThread* const me) {
    cleanUpRelations(me);
}

void GasProcessingThread_processData(GasProcessingThread* const me) {
    GasData* gPtr;
    
    /* Pull data from the queue and process it */
    gPtr = GasDataQueue_remove(me->itsGasDataQueue);
    if (gPtr != NULL) {
        GasController_handleGasData(&(me->itsGasController), gPtr);
    }
}

struct GasDataQueue* GasProcessingThread_getItsGasDataQueue(const GasProcessingThread* const me) {
    return (struct GasDataQueue*)me->itsGasDataQueue;
}

void GasProcessingThread_setItsGasDataQueue(GasProcessingThread* const me, struct GasDataQueue* p_GasDataQueue) {
    me->itsGasDataQueue = p_GasDataQueue;
}

GasProcessingThread* GasProcessingThread_Create(void) {
    GasProcessingThread* me = (GasProcessingThread*)malloc(sizeof(GasProcessingThread));
    if (me != NULL) {
        GasProcessingThread_Init(me);
    }
    return me;
}

void GasProcessingThread_Destroy(GasProcessingThread* const me) {
    if (me != NULL) {
        GasProcessingThread_Cleanup(me);
    }
    free(me);
}

static void initRelations(GasProcessingThread* const me) {
    GasController_Init(&(me->itsGasController));
}

static void cleanUpRelations(GasProcessingThread* const me) {
    GasController_Cleanup(&(me->itsGasController));
}
