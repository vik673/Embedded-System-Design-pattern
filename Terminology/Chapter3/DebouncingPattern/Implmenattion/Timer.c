#include "Timer.h"
#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP_MS(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define SLEEP_MS(ms) usleep((ms) * 1000)
#endif

void Timer_Init(Timer* const me) {
    me->resolution_ms = 1;  /* Default 1ms resolution */
}

void Timer_Cleanup(Timer* const me) {
    /* Nothing to clean up for this simple implementation */
}

Timer* Timer_Create(void) {
    Timer* me = (Timer*)malloc(sizeof(Timer));
    if (me != NULL) {
        Timer_Init(me);
    }
    return me;
}

void Timer_Destroy(Timer* const me) {
    if (me != NULL) {
        Timer_Cleanup(me);
        free(me);
    }
}

void Timer_delay(Timer* const me, unsigned int ms) {
    printf("Timer: Delaying for %u ms (debounce period)\n", ms);
    
    /* Adjust delay to timer resolution */
    unsigned int adjusted_ms = ((ms + me->resolution_ms - 1) / me->resolution_ms) * me->resolution_ms;
    
    if (adjusted_ms != ms) {
        printf("Timer: Adjusted delay to %u ms due to resolution\n", adjusted_ms);
    }
    
    /* Platform-specific sleep implementation */
    SLEEP_MS(adjusted_ms);
}

void Timer_setResolution(Timer* const me, unsigned int resolution_ms) {
    me->resolution_ms = resolution_ms;
    printf("Timer: Resolution set to %u ms\n", resolution_ms);
}

unsigned int Timer_getResolution(const Timer* const me) {
    return me->resolution_ms;
}
