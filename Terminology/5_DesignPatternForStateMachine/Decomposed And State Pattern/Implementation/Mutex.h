#ifndef Mutex_H
#define Mutex_H

typedef struct Mutex Mutex;
struct Mutex {
    int locked;
    int owner_id;
};

void Mutex_Init(Mutex* const me);
void Mutex_Cleanup(Mutex* const me);
int Mutex_lock(Mutex* const me);
int Mutex_release(Mutex* const me);
int Mutex_isLocked(const Mutex* const me);
Mutex * Mutex_Create(void);
void Mutex_Destroy(Mutex* const me);

#endif
