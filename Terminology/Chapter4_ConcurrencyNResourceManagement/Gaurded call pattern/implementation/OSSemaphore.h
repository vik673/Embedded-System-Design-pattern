#ifndef OSSemaphore_H
#define OSSemaphore_H

typedef struct OSSemaphore OSSemaphore;
struct OSSemaphore {
    int locked;     /* 0 = unlocked, 1 = locked */
    int mutexID;    /* identifier for the mutex */
};

/* Constructors and destructors */
void OSSemaphore_Init(OSSemaphore* const me);
void OSSemaphore_Cleanup(OSSemaphore* const me);

/* Operations */
void OSSemaphore_lock(OSSemaphore* const me);
void OSSemaphore_release(OSSemaphore* const me);

OSSemaphore* OSSemaphore_Create(void);
void OSSemaphore_Destroy(OSSemaphore* const me);

#endif
