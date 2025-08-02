#ifndef SimMutex_H
#define SimMutex_H

typedef struct SimMutex {
    int locked;
    int owner_thread_id;
} SimMutex;

/* Function declarations */
void SimMutex_lock(SimMutex* const me);
void SimMutex_release(SimMutex* const me);
int SimMutex_tryLock(SimMutex* const me);

#endif
