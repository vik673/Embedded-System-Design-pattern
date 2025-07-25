#include "Mutex.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Create a new mutex
 * @return Pointer to newly created mutex, or NULL on failure
 */
Mutex* Mutex_Create(void) {
    Mutex* me = (Mutex*)malloc(sizeof(Mutex));
    if (me != NULL) {
        Mutex_Init(me);
    }
    return me;
}

/**
 * @brief Destroy a mutex
 * @param me Pointer to the mutex to destroy
 */
void Mutex_Destroy(Mutex* const me) {
    if (me != NULL) {
        free(me);
    }
}

/**
 * @brief Initialize a mutex
 * @param me Pointer to the mutex to initialize
 */
void Mutex_Init(Mutex* const me) {
    if (me != NULL) {
        me->locked = 0;
        me->owner_id = -1;
    }
}

/**
 * @brief Lock the mutex
 * @param me Pointer to the mutex to lock
 * @return 0 on success, -1 on failure
 */
int Mutex_lock(Mutex* const me) {
    if (me == NULL) {
        return -1;
    }
    
    /* In a real implementation, this would use OS-specific locking mechanisms */
    /* For this example, we simulate a simple lock */
    if (me->locked == 0) {
        me->locked = 1;
        me->owner_id = 1; /* Simulate current thread ID */
        return 0;
    }
    
    /* Mutex already locked */
    return -1;
}

/**
 * @brief Release (unlock) the mutex
 * @param me Pointer to the mutex to release
 * @return 0 on success, -1 on failure
 */
int Mutex_release(Mutex* const me) {
    if (me == NULL) {
        return -1;
    }
    
    if (me->locked == 1) {
        me->locked = 0;
        me->owner_id = -1;
        return 0;
    }
    
    /* Mutex was not locked */
    return -1;
}

/**
 * @brief Check if mutex is locked
 * @param me Pointer to the mutex to check
 * @return 1 if locked, 0 if unlocked
 */
int Mutex_isLocked(const Mutex* const me) {
    if (me == NULL) {
        return 0;
    }
    return me->locked;
}
