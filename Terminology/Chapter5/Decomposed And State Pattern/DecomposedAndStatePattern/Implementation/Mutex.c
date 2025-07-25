#include "Mutex.h"
#include <stdlib.h>

void Mutex_Init(Mutex* const me) {
    me->locked = 0;
    me->owner_id = -1;
}

void Mutex_Cleanup(Mutex* const me) {
    // Nothing to cleanup for now
}

int Mutex_lock(Mutex* const me) {
    if (!me->locked) {
        me->locked = 1;
        me->owner_id = 1; // Simple owner ID for demo
        return 1; // Success
    }
    return 0; // Failed to acquire lock
}

int Mutex_release(Mutex* const me) {
    if (me->locked) {
        me->locked = 0;
        me->owner_id = -1;
        return 1; // Success
    }
    return 0; // Was not locked
}

int Mutex_isLocked(const Mutex* const me) {
    return me->locked;
}

Mutex * Mutex_Create(void) {
    Mutex* me = (Mutex *)malloc(sizeof(Mutex));
    if(me!=NULL)
        Mutex_Init(me);
    return me;
}

void Mutex_Destroy(Mutex* const me) {
    if(me!=NULL)
        Mutex_Cleanup(me);
    free(me);
}
