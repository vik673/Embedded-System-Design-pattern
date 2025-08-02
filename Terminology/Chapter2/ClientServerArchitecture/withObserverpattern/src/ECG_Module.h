#ifndef ECG_Module_H
#define ECG_Module_H

#include <stdio.h>
#include "ECGPkg.h"

struct TMDQueue;

/* class ECG_Module */
typedef struct ECG_Module ECG_Module;

struct ECG_Module {
    struct TMDQueue* itsTMDQueue;
};

/* Constructors and destructors:*/
void ECG_Module_Init(ECG_Module* const me);
void ECG_Module_Cleanup(ECG_Module* const me);

/* Operations */
void ECG_Module_getDataSample(ECG_Module* const me);

struct TMDQueue* ECG_Module_getItsTMDQueue(const ECG_Module* const me);
void ECG_Module_setItsTMDQueue(ECG_Module* const me, struct TMDQueue* p_TMDQueue);

ECG_Module* ECG_Module_Create(void);
void ECG_Module_Destroy(ECG_Module* const me);

#endif
