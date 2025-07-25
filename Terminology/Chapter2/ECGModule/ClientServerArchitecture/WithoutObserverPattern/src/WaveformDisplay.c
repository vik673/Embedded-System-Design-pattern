#include "WaveformDisplay.h"
#include "TMDQueue.h"

static void cleanUpRelations(WaveformDisplay* const me);

void WaveformDisplay_Init(WaveformDisplay* const me) {
    me->index = 0;
    me->itsTMDQueue = NULL;
}

void WaveformDisplay_Cleanup(WaveformDisplay* const me) {
    cleanUpRelations(me);
}

/* operation getScalarValue() */
void WaveformDisplay_getScalarValue(WaveformDisplay* const me) {
    TimeMarkedData tmd;
    tmd = TMDQueue_remove(me->itsTMDQueue, me->index);
    printf(" Waveform index: %d TimeInterval: %ld DataValue: %d\n", 
           me->index, tmd.timeInterval, tmd.dataValue);
    me->index = TMDQueue_getNextIndex(me->itsTMDQueue, me->index);
}

/* operation updateDisplay() */
void WaveformDisplay_updateDisplay(WaveformDisplay* const me) {
    /* put some display update code here… */
}

struct TMDQueue* WaveformDisplay_getItsTMDQueue(const WaveformDisplay* const me) {
    return (struct TMDQueue*)me->itsTMDQueue;
}

void WaveformDisplay_setItsTMDQueue(WaveformDisplay* const me, struct TMDQueue* p_TMDQueue) {
    me->itsTMDQueue = p_TMDQueue;
}

WaveformDisplay* WaveformDisplay_Create(void) {
    WaveformDisplay* me = (WaveformDisplay*)malloc(sizeof(WaveformDisplay));
    if (me != NULL) {
        WaveformDisplay_Init(me);
    }
    return me;
}

void WaveformDisplay_Destroy(WaveformDisplay* const me) {
    if (me != NULL) {
        WaveformDisplay_Cleanup(me);
    }
    free(me);
}

static void cleanUpRelations(WaveformDisplay* const me) {
    if (me->itsTMDQueue != NULL) {
        me->itsTMDQueue = NULL;
    }
}
