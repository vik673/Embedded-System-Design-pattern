#ifndef MUTEX_H
#define MUTEX_H

typedef struct Mutex Mutex;

struct Mutex {
    int locked;
    /* In a real implementation, this would contain */
    /* OS-specific mutex data */
};

/* Constructors and destructors */
void Mutex_Init(Mutex* const me);
void Mutex_Cleanup(Mutex* const me);

/* Operations */
void Mutex_lock(Mutex* const me);
void Mutex_release(Mutex* const me);

/* Memory management */
Mutex* Mutex_Create(void);
void Mutex_Destroy(Mutex* const me);

#endif
