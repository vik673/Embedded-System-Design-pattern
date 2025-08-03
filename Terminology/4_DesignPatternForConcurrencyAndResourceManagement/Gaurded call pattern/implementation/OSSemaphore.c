#include "OSSemaphore.h"
#include "GuardedCallExample.h"
#include <stdio.h>

static int nextMutexID = 1;

void OSSemaphore_Init(OSSemaphore* const me) {
    me->locked = 0;  /* Initially unlocked */
    me->mutexID = nextMutexID++;
}

void OSSemaphore_Cleanup(OSSemaphore* const me) {
    /* Nothing specific to clean up in this simple implementation */
}

void OSSemaphore_lock(OSSemaphore* const me) {
    if (me->locked == 0) {
        me->locked = 1;
        printf("Semaphore %d locked\n", me->mutexID);
    } else {
        printf("Semaphore %d already locked - task would block\n", me->mutexID);
        /* In a real RTOS, this would block the current task */
    }
}

void OSSemaphore_release(OSSemaphore* const me) {
    if (me->locked == 1) {
        me->locked = 0;
        printf("Semaphore %d released\n", me->mutexID);
        /* In a real RTOS, this would unblock waiting tasks */
    }
}

OSSemaphore* OSSemaphore_Create(void) {
    OSSemaphore* me = (OSSemaphore*) malloc(sizeof(OSSemaphore));
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

/* OS API Implementation */
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
