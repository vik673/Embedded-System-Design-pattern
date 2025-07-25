#ifndef MUTEX_H
#define MUTEX_H

typedef struct Mutex Mutex;

struct Mutex {
    int locked;  /* 0 = unlocked, 1 = locked */
    int owner;   /* Thread/task ID that owns the lock */
};

/* Constructors and destructors */
void Mutex_Init(Mutex* const me);
void Mutex_Cleanup(Mutex* const me);

/* Operations */
int Mutex_lock(Mutex* const me);
void Mutex_release(Mutex* const me);

/* Creation and destruction */
Mutex* Mutex_Create(void);
void Mutex_Destroy(Mutex* const me);

#endif /* MUTEX_H */
