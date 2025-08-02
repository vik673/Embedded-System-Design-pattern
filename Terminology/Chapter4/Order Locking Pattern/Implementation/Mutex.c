#include "Mutex.h"
#include <stdlib.h>

void Mutex_Init(Mutex* const me) {
    me->locked = 0;
    me->owner = -1;
}

void Mutex_Cleanup(Mutex* const me) {
    /* Nothing special to clean up for this simple implementation */
}

int Mutex_lock(Mutex* const me) {
    /* Simple implementation - in real system this would use OS primitives */
    if (me->locked) {
        return -1; /* Already locked */
    }
    me->locked = 1;
    me->owner = 1; /* Simplified - would be actual thread ID */
    return 0;
}

void Mutex_release(Mutex* const me) {
    me->locked = 0;
    me->owner = -1;
}

Mutex* Mutex_Create(void) {
    Mutex* me = (Mutex*)malloc(sizeof(Mutex));
    if (me != NULL) {
        Mutex_Init(me);
    }
    return me;
}

void Mutex_Destroy(Mutex* const me) {
    if (me != NULL) {
        Mutex_Cleanup(me);
        free(me);
    }
}
