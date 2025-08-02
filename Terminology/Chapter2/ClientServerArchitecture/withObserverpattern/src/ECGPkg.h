#ifndef ECGPkg_H
#define ECGPkg_H

#include <stdio.h>
#include <stdlib.h>

/* forward declarations */
struct ArrythmiaDetector;
struct ECG_Module;
struct HistogramDisplay;
struct QRSDetector;
struct TMDQueue;
struct TestBuilder;
struct TimeMarkedData;
struct WaveformDisplay;
struct NotificationHandle;

typedef unsigned char boolean;
typedef void (*UpdateFuncPtr)(void* clientPtr, const struct TimeMarkedData tmd);

#define QUEUE_SIZE (20000)

#endif
