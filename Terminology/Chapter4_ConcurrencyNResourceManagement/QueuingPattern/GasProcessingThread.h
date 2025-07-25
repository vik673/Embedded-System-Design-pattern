#ifndef GasProcessingThread_H
#define GasProcessingThread_H

#include "QueuingExample.h"
#include "GasDataQueue.h"
#include "GasController.h"

typedef struct GasProcessingThread GasProcessingThread;
struct GasProcessingThread {
    struct GasController itsGasController;
    struct GasDataQueue* itsGasDataQueue;
};

/* Constructors and destructors */
void GasProcessingThread_Init(GasProcessingThread* const me);
void GasProcessingThread_Cleanup(GasProcessingThread* const me);

/* Operations */
void GasProcessingThread_processData(GasProcessingThread* const me);

/* Relations */
struct GasDataQueue* GasProcessingThread_getItsGasDataQueue(const GasProcessingThread* const me);
void GasProcessingThread_setItsGasDataQueue(GasProcessingThread* const me, struct GasDataQueue* p_GasDataQueue);

GasProcessingThread* GasProcessingThread_Create(void);
void GasProcessingThread_Destroy(GasProcessingThread* const me);

#endif
