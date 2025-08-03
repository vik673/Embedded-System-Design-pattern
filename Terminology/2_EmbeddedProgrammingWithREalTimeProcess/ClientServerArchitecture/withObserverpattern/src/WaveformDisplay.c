#include "WaveformDisplay.h"
#include "TimeMarkedData.h"
#include "TMDQueue.h"

static void cleanUpRelations(WaveformDisplay* const me);

void WaveformDisplay_Init(WaveformDisplay* const me) {
    me->itsTMDQueue = NULL;
}

void WaveformDisplay_Cleanup(WaveformDisplay* const me) {
    /* remove yourself from server subscription list */
    if (me->itsTMDQueue != NULL) {
        TMDQueue_unsubscribe(me->itsTMDQueue, WaveformDisplay_update);
    }
    cleanUpRelations(me);
}

void WaveformDisplay_update(WaveformDisplay* const me, const struct TimeMarkedData tmd) {
    printf(" Waveform -> TimeInterval: %ld DataValue: %d\n", tmd.timeInterval, tmd.dataValue);
}

void WaveformDisplay_updateDisplay(WaveformDisplay* const me) {
    /* put some display update code here */
}

struct TMDQueue* WaveformDisplay_getItsTMDQueue(const WaveformDisplay* const me) {
    return (struct TMDQueue*)me->itsTMDQueue;
}

void WaveformDisplay_setItsTMDQueue(WaveformDisplay* const me, struct TMDQueue* p_TMDQueue) {
    me->itsTMDQueue = p_TMDQueue;
    /* call subscribe to connect to the server */
    if (p_TMDQueue != NULL) {
        TMDQueue_subscribe(me->itsTMDQueue, WaveformDisplay_update);
    }
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
