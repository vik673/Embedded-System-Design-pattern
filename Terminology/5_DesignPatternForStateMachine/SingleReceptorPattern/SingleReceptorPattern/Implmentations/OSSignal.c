#include "TokenizerAsyncSinglePkg.h"
#include <stdio.h>

/* Simple OS signal simulation for demonstration */
static int signal_posted = 0;

void postSignal(void) {
    signal_posted = 1;
    printf("Signal posted\n");
}

void waitOnSignal(void) {
    while (!signal_posted) {
        /* In a real implementation, this would be an OS call */
        /* For demo purposes, we'll just busy wait */
    }
    signal_posted = 0; /* Reset the signal */
    printf("Signal received\n");
}
