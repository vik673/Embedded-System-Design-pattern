#ifndef WaveformDisplay_H
#define WaveformDisplay_H

#include <stdio.h>
#include "ECGPkg.h"

struct TMDQueue;

/* class WaveformDisplay */
typedef struct WaveformDisplay WaveformDisplay;

struct WaveformDisplay {
    int index;
    struct TMDQueue* itsTMDQueue;
};

/* Constructors and destructors:*/
void WaveformDisplay_Init(WaveformDisplay* const me);
void WaveformDisplay_Cleanup(WaveformDisplay* const me);

/* Operations */
void WaveformDisplay_getScalarValue(WaveformDisplay* const me);
void WaveformDisplay_updateDisplay(WaveformDisplay* const me);

struct TMDQueue* WaveformDisplay_getItsTMDQueue(const WaveformDisplay* const me);
void WaveformDisplay_setItsTMDQueue(WaveformDisplay* const me, struct TMDQueue* p_TMDQueue);

WaveformDisplay* WaveformDisplay_Create(void);
void WaveformDisplay_Destroy(WaveformDisplay* const me);

#endif
