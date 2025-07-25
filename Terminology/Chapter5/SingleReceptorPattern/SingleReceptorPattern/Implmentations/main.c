#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TokenizerCommonPkg.h"  /* Include this for Event types */
#include "TSRSyncSingleReceptor.h"
#include "TSRAsyncSingleReceptor.h"
#include "TSREventQueue.h"
#include "Mutex.h"

/* Helper function to create an event */
Event createEvent(EventType type, char c) {
    Event e;
    e.eType = type;
    e.ed.c = c;
    return e;
}

/* Test synchronous version */
void testSynchronousReceptor() {
    printf("\n=== Testing Synchronous Single Receptor ===\n");
    
    TokenizerSyncSingleReceptor* receptor = TokenizerSyncSingleReceptor_Create();
    if (!receptor) {
        printf("Error: Failed to create sync receptor\n");
        return;
    }
    
    Mutex* mutex = Mutex_Create();
    if (!mutex) {
        printf("Error: Failed to create mutex\n");
        TokenizerSyncSingleReceptor_Destroy(receptor);
        return;
    }
    
    TokenizerSyncSingleReceptor_setItsMutex(receptor, mutex);
    
    /* Test parsing "123.45" */
    printf("Parsing: 123.45\n");
    
    TokenizerSyncSingleReceptor_eventDispatch(receptor, createEvent(EVDIGIT, '1'));
    TokenizerSyncSingleReceptor_eventDispatch(receptor, createEvent(EVDIGIT, '2'));
    TokenizerSyncSingleReceptor_eventDispatch(receptor, createEvent(EVDIGIT, '3'));
    TokenizerSyncSingleReceptor_eventDispatch(receptor, createEvent(EVDOT, '.'));
    TokenizerSyncSingleReceptor_eventDispatch(receptor, createEvent(EVDIGIT, '4'));
    TokenizerSyncSingleReceptor_eventDispatch(receptor, createEvent(EVDIGIT, '5'));
    TokenizerSyncSingleReceptor_eventDispatch(receptor, createEvent(EVWHITESPACE, ' '));
    
    /* Test parsing "0.789" */
    printf("\nParsing: 0.789\n");
    
    TokenizerSyncSingleReceptor_eventDispatch(receptor, createEvent(EVDIGIT, '0'));
    TokenizerSyncSingleReceptor_eventDispatch(receptor, createEvent(EVDOT, '.'));
    TokenizerSyncSingleReceptor_eventDispatch(receptor, createEvent(EVDIGIT, '7'));
    TokenizerSyncSingleReceptor_eventDispatch(receptor, createEvent(EVDIGIT, '8'));
    TokenizerSyncSingleReceptor_eventDispatch(receptor, createEvent(EVDIGIT, '9'));
    TokenizerSyncSingleReceptor_eventDispatch(receptor, createEvent(EVENDOFSTRING, '\0'));
    
    TokenizerSyncSingleReceptor_Destroy(receptor);
    Mutex_Destroy(mutex);
}

/* Test asynchronous version (simplified without actual threading) */
void testAsynchronousReceptor() {
    printf("\n=== Testing Asynchronous Single Receptor ===\n");
    
    TokenizerAsyncSingleReceptor* receptor = TokenizerAsyncSingleReceptor_Create();
    if (!receptor) {
        printf("Error: Failed to create async receptor\n");
        return;
    }
    
    TSREventQueue* queue = TSREventQueue_Create();
    if (!queue) {
        printf("Error: Failed to create event queue\n");
        TokenizerAsyncSingleReceptor_Destroy(receptor);
        return;
    }
    
    Mutex* mutex = Mutex_Create();
    if (!mutex) {
        printf("Error: Failed to create mutex for async version\n");
        TSREventQueue_Destroy(queue);
        TokenizerAsyncSingleReceptor_Destroy(receptor);
        return;
    }
    
    TSREventQueue_setItsMutex(queue, mutex);
    TokenizerAsyncSingleReceptor_setItsTSREventQueue(receptor, queue);
    
    printf("Posting events to queue: 42.7\n");
    
    /* Post events to the queue */
    if (TSREventQueue_post(queue, createEvent(EVDIGIT, '4')) == 0 &&
        TSREventQueue_post(queue, createEvent(EVDIGIT, '2')) == 0 &&
        TSREventQueue_post(queue, createEvent(EVDOT, '.')) == 0 &&
        TSREventQueue_post(queue, createEvent(EVDIGIT, '7')) == 0 &&
        TSREventQueue_post(queue, createEvent(EVWHITESPACE, ' ')) == 0) {
        
        /* Process events (normally this would be in a separate thread) */
        printf("Processing events from queue:\n");
        while (!TSREventQueue_isEmpty(queue)) {
            TokenizerAsyncSingleReceptor_eventDispatch(receptor,
                TSREventQueue_pull(queue));
        }
    } else {
        printf("Error: Failed to post events to queue\n");
    }
    
    TokenizerAsyncSingleReceptor_Destroy(receptor);
    TSREventQueue_Destroy(queue);
    Mutex_Destroy(mutex);
}

int main() {
    printf("Single Event Receptor Pattern Demo\n");
    printf("===================================\n");
    
    testSynchronousReceptor();
    testAsynchronousReceptor();
    
    printf("\nDemo completed successfully!\n");
    return 0;
}
