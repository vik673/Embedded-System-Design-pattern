#ifndef Timer_H
#define Timer_H

typedef struct Timer Timer;
struct Timer {
    unsigned int resolution_ms;  /* Timer resolution in milliseconds */
};

/* Constructor and Destructor */
void Timer_Init(Timer* const me);
void Timer_Cleanup(Timer* const me);
Timer* Timer_Create(void);
void Timer_Destroy(Timer* const me);

/* Operations */
void Timer_delay(Timer* const me, unsigned int ms);
void Timer_setResolution(Timer* const me, unsigned int resolution_ms);
unsigned int Timer_getResolution(const Timer* const me);

#endif
