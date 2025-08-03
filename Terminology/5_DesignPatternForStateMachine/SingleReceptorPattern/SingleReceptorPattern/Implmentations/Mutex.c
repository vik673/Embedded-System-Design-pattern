#include "Mutex.h"
#include <stdlib.h>

void Mutex_Init(Mutex* const me) {
    me->locked = 0;
}

void Mutex_Cleanup(Mutex* const me) {
    /* cleanup if needed */
}

void Mutex_lock(Mutex* const me) {
    /* In a real implementation, this would use */
    /* OS-specific mutex locking */
    me->locked = 1;
}

void Mutex_release(Mutex* const me) {
    /* In a real implementation, this would use */
    /* OS-specific mutex unlocking */
    me->locked = 0;
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
