#ifndef MUTEX_H
#define MUTEX_H

/**
 * @file Mutex.h
 * @brief Mutex interface for thread-safe operations in Multiple Receptor Pattern
 * 
 * This file defines the Mutex interface used to ensure deterministic 
 * run-to-completion semantics of state machine transitions.
 */

/**
 * @brief Mutex structure for synchronization
 */
typedef struct Mutex {
    int locked;         /**< Lock status: 0 = unlocked, 1 = locked */
    int owner_id;       /**< ID of the thread/task that owns the lock */
} Mutex;

/**
 * @brief Create a new mutex
 * @return Pointer to newly created mutex, or NULL on failure
 */
Mutex* Mutex_Create(void);

/**
 * @brief Destroy a mutex
 * @param me Pointer to the mutex to destroy
 */
void Mutex_Destroy(Mutex* const me);

/**
 * @brief Initialize a mutex
 * @param me Pointer to the mutex to initialize
 */
void Mutex_Init(Mutex* const me);

/**
 * @brief Lock the mutex
 * @param me Pointer to the mutex to lock
 * @return 0 on success, -1 on failure
 */
int Mutex_lock(Mutex* const me);

/**
 * @brief Release (unlock) the mutex
 * @param me Pointer to the mutex to release
 * @return 0 on success, -1 on failure
 */
int Mutex_release(Mutex* const me);

/**
 * @brief Check if mutex is locked
 * @param me Pointer to the mutex to check
 * @return 1 if locked, 0 if unlocked
 */
int Mutex_isLocked(const Mutex* const me);

#endif /* MUTEX_H */
