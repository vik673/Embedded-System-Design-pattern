#ifndef OSSemaphore_H
#define OSSemaphore_H

#include "QueuingExample.h"

typedef struct OSSemaphore OSSemaphore;
struct OSSemaphore {
    int locked;
};

/* Constructors and destructors */
void OSSemaphore_Init(OSSemaphore* const me);
void OSSemaphore_Cleanup(OSSemaphore* const me);
OSSemaphore* OSSemaphore_Create(void);
void OSSemaphore_Destroy(OSSemaphore* const me);

/* Operations */
void OSSemaphore_lock(OSSemaphore* const me);
void OSSemaphore_release(OSSemaphore* const me);

#endif
