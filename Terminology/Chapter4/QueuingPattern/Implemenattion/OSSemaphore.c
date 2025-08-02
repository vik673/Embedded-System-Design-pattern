#include "OSSemaphore.h"

void OSSemaphore_Init(OSSemaphore* const me) {
    me->locked = 0;
}

void OSSemaphore_Cleanup(OSSemaphore* const me) {
    /* Nothing to cleanup for this simple implementation */
}

OSSemaphore* OSSemaphore_Create(void) {
    OSSemaphore* me = (OSSemaphore*)malloc(sizeof(OSSemaphore));
    if (me != NULL) {
        OSSemaphore_Init(me);
    }
    return me;
}

void OSSemaphore_Destroy(OSSemaphore* const me) {
    if (me != NULL) {
        OSSemaphore_Cleanup(me);
    }
    free(me);
}

void OSSemaphore_lock(OSSemaphore* const me) {
    /* Simple spinlock implementation for demonstration */
    while (me->locked) {
        /* Wait for unlock */
    }
    me->locked = 1;
}

void OSSemaphore_release(OSSemaphore* const me) {
    me->locked = 0;
}

/* OS semaphore services wrapper functions */
struct OSSemaphore* OS_create_semaphore(void) {
    return OSSemaphore_Create();
}

void OS_destroy_semaphore(struct OSSemaphore* sPtr) {
    OSSemaphore_Destroy(sPtr);
}

void OS_lock_semaphore(struct OSSemaphore* sPtr) {
    OSSemaphore_lock(sPtr);
}

void OS_release_semaphore(struct OSSemaphore* sPtr) {
    OSSemaphore_release(sPtr);
}
