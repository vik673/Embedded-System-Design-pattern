#ifndef ArrythmiaDetector_H
#define ArrythmiaDetector_H

#include <stdio.h>
#include "ECGPkg.h"

struct TMDQueue;

/* class ArrythmiaDetector */
typedef struct ArrythmiaDetector ArrythmiaDetector;

struct ArrythmiaDetector {
    int index;
    struct TMDQueue* itsTMDQueue;
};

/* Constructors and destructors:*/
void ArrythmiaDetector_Init(ArrythmiaDetector* const me);
void ArrythmiaDetector_Cleanup(ArrythmiaDetector* const me);

/* Operations */
void ArrythmiaDetector_getDataSample(ArrythmiaDetector* const me);
void ArrythmiaDetector_detectArrythmia(ArrythmiaDetector* const me);

struct TMDQueue* ArrythmiaDetector_getItsTMDQueue(const ArrythmiaDetector* const me);
void ArrythmiaDetector_setItsTMDQueue(ArrythmiaDetector* const me, struct TMDQueue* p_TMDQueue);

ArrythmiaDetector* ArrythmiaDetector_Create(void);
void ArrythmiaDetector_Destroy(ArrythmiaDetector* const me);

#endif
