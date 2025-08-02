#ifndef QRSDetector_H
#define QRSDetector_H

#include <stdio.h>
#include "ECGPkg.h"

struct TMDQueue;

/* class QRSDetector */
typedef struct QRSDetector QRSDetector;

struct QRSDetector {
    struct TMDQueue* itsTMDQueue;
};

/* Constructors and destructors:*/
void QRSDetector_Init(QRSDetector* const me);
void QRSDetector_Cleanup(QRSDetector* const me);

/* Operations */
void QRSDetector_update(QRSDetector* const me, const struct TimeMarkedData tmd);
void QRSDetector_detectQRS(QRSDetector* const me);

struct TMDQueue* QRSDetector_getItsTMDQueue(const QRSDetector* const me);
void QRSDetector_setItsTMDQueue(QRSDetector* const me, struct TMDQueue* p_TMDQueue);

QRSDetector* QRSDetector_Create(void);
void QRSDetector_Destroy(QRSDetector* const me);

#endif
