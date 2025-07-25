#include "StateTableTokenizer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief Initialize the state table with transitions and actions
 * @param me Pointer to the tokenizer instance
 */
static void initializeStateTable(StateTableTokenizer* const me);

/**
 * @brief Clean up internal relations
 * @param me Pointer to the tokenizer instance
 */
static void cleanUpRelations(StateTableTokenizer* const me);

/* ============================================================================
 * Constructors and Destructors
 * ============================================================================ */

StateTableTokenizer* StateTableTokenizer_Create(void) {
    StateTableTokenizer* me = (StateTableTokenizer*)malloc(sizeof(StateTableTokenizer));
    if (me != NULL) {
        me->context = (TokenizerContext*)malloc(sizeof(TokenizerContext));
        if (me->context != NULL) {
            StateTableTokenizer_Init(me);
        } else {
            free(me);
            me = NULL;
        }
    }
    return me;
}

void StateTableTokenizer_Destroy(StateTableTokenizer* const me) {
    if (me != NULL) {
        StateTableTokenizer_Cleanup(me);
        if (me->context != NULL) {
            free(me->context);
        }
        free(me);
    }
}

void StateTableTokenizer_Init(StateTableTokenizer* const me) {
    if (me == NULL || me->context == NULL) return;
    
    /* Initialize context */
    me->context->currentState = STATE_NONUMBER;
    me->context->currentChar = '\0';
    me->context->result = 0.0;
    me->context->tensPlace = 10.0;
    me->context->mutex = NULL;
    me->context->transitionCount = 0;
    
    /* Reset event counters */
    for (int i = 0; i < EVENT_MAX; i++) {
        me->context->eventCount[i] = 0;
    }
    
    /* Initialize the state table */
    initializeStateTable(me);
    
    printf("StateTableTokenizer initialized\n");
}

void StateTableTokenizer_Cleanup(StateTableTokenizer* const me) {
    if (me != NULL) {
        cleanUpRelations(me);
    }
}

/* ============================================================================
 * Core State Table Pattern Implementation
 * ============================================================================ */

int StateTableTokenizer_ProcessEvent(StateTableTokenizer* const me, 
                                    EventType event, 
                                    char eventData) {
    if (me == NULL || me->context == NULL) {
        return -1;
    }
    
    if (event >= EVENT_MAX || me->context->currentState >= STATE_MAX) {
        printf("Error: Invalid event (%d) or state (%d)\n", event, me->context->currentState);
        return -1;
    }
    
    /* Lock mutex for thread safety */
    if (me->context->mutex != NULL) {
        if (Mutex_lock(me->context->mutex) != 0) {
            printf("Error: Failed to acquire mutex\n");
            return -1;
        }
    }
    
    /* Update statistics */
    me->context->eventCount[event]++;
    me->context->transitionCount++;
    
    /* Get the state table entry */
    StateTableEntry* entry = &me->stateTable[me->context->currentState][event];
    
    printf("State Transition: %s + %s -> %s (Action: %s)\n",
           stateToString(me->context->currentState),
           eventToString(event),
           stateToString(entry->nextState),
           actionToString(entry->actionType));
    
    /* Store event data */
    me->context->currentChar = eventData;
    
    /* Execute the action if defined */
    if (entry->actionFunc != NULL) {
        entry->actionFunc(me->context, eventData);
    }
    
    /* Transition to the next state */
    me->context->currentState = entry->nextState;
    
    /* Release mutex */
    if (me->context->mutex != NULL) {
        Mutex_release(me->context->mutex);
    }
    
    return 0;
}

StateType StateTableTokenizer_GetCurrentState(const StateTableTokenizer* const me) {
    if (me == NULL || me->context == NULL) {
        return STATE_MAX; /* Invalid state */
    }
    return me->context->currentState;
}

double StateTableTokenizer_GetResult(const StateTableTokenizer* const me) {
    if (me == NULL || me->context == NULL) {
        return 0.0;
    }
    return me->context->result;
}

/* ============================================================================
 * Convenience Event Processing Methods
 * ============================================================================ */

int StateTableTokenizer_ProcessDigit(StateTableTokenizer* const me, char c) {
    return StateTableTokenizer_ProcessEvent(me, EVENT_DIGIT, c);
}

int StateTableTokenizer_ProcessDot(StateTableTokenizer* const me) {
    return StateTableTokenizer_ProcessEvent(me, EVENT_DOT, '.');
}

int StateTableTokenizer_ProcessWhitespace(StateTableTokenizer* const me) {
    return StateTableTokenizer_ProcessEvent(me, EVENT_WHITESPACE, ' ');
}

int StateTableTokenizer_ProcessEndOfString(StateTableTokenizer* const me) {
    return StateTableTokenizer_ProcessEvent(me, EVENT_END_OF_STRING, '\0');
}

/* ============================================================================
 * Mutex Management
 * ============================================================================ */

void StateTableTokenizer_SetMutex(StateTableTokenizer* const me, Mutex* mutex) {
    if (me != NULL && me->context != NULL) {
        me->context->mutex = mutex;
    }
}

Mutex* StateTableTokenizer_GetMutex(const StateTableTokenizer* const me) {
    if (me == NULL || me->context == NULL) {
        return NULL;
    }
    return me->context->mutex;
}

/* ============================================================================
 * Debugging and Statistics
 * ============================================================================ */

void StateTableTokenizer_PrintStateTable(const StateTableTokenizer* const me) {
    if (me == NULL) return;
    
    printf("\n=== State Transition Table ===\n");
    printf("%-20s %-18s %-25s %-20s\n", "Current State", "Event", "Next State", "Action");
    printf("%-20s %-18s %-25s %-20s\n", "============", "=====", "==========", "======");
    
    for (int state = 0; state < STATE_MAX; state++) {
        for (int event = 0; event < EVENT_MAX; event++) {
            StateTableEntry* entry = &me->stateTable[state][event];
            printf("%-20s %-18s %-25s %-20s\n",
                   stateToString((StateType)state),
                   eventToString((EventType)event),
                   stateToString(entry->nextState),
                   actionToString(entry->actionType));
        }
    }
    printf("===============================\n\n");
}

void StateTableTokenizer_PrintStatistics(const StateTableTokenizer* const me) {
    if (me == NULL || me->context == NULL) return;
    
    printf("\n=== Tokenizer Statistics ===\n");
    printf("Current State: %s\n", stateToString(me->context->currentState));
    printf("Current Result: %g\n", me->context->result);
    printf("Total Transitions: %d\n", me->context->transitionCount);
    printf("\nEvent Counts:\n");
    
    for (int i = 0; i < EVENT_MAX; i++) {
        printf("  %s: %d\n", eventToString((EventType)i), me->context->eventCount[i]);
    }
    printf("=============================\n\n");
}

void StateTableTokenizer_ResetStatistics(StateTableTokenizer* const me) {
    if (me == NULL || me->context == NULL) return;
    
    me->context->transitionCount = 0;
    for (int i = 0; i < EVENT_MAX; i++) {
        me->context->eventCount[i] = 0;
    }
}

/* ============================================================================
 * Action Functions Implementation
 * ============================================================================ */

void action_none(TokenizerContext* context, char eventData) {
    /* No action required */
    (void)context;    /* Suppress unused parameter warning */
    (void)eventData;  /* Suppress unused parameter warning */
}

void action_start_number(TokenizerContext* context, char eventData) {
    if (context == NULL) return;
    
    context->result = (double)digit(eventData);
    context->tensPlace = 10.0;
    printf("Started new number with digit '%c', result = %g\n", eventData, context->result);
}

void action_add_digit_whole(TokenizerContext* context, char eventData) {
    if (context == NULL) return;
    
    context->result = context->result * 10.0 + digit(eventData);
    printf("Added digit '%c' to whole part, result = %g\n", eventData, context->result);
}

void action_add_digit_fractional(TokenizerContext* context, char eventData) {
    if (context == NULL) return;
    
    context->result += digit(eventData) / context->tensPlace;
    context->tensPlace *= 10.0;
    printf("Added digit '%c' to fractional part, result = %g\n", eventData, context->result);
}

void action_start_fractional(TokenizerContext* context, char eventData) {
    if (context == NULL) return;
    
    context->tensPlace = 10.0;
    printf("Started fractional part processing\n");
    (void)eventData;  /* Suppress unused parameter warning */
}

void action_finish_number(TokenizerContext* context, char eventData) {
    if (context == NULL) return;
    
    printf("Finished number: %g\n", context->result);
    (void)eventData;  /* Suppress unused parameter warning */
}

void action_reset(TokenizerContext* context, char eventData) {
    if (context == NULL) return;
    
    context->result = 0.0;
    context->tensPlace = 10.0;
    printf("Reset tokenizer\n");
    (void)eventData;  /* Suppress unused parameter warning */
}

/* ============================================================================
 * Private Helper Functions
 * ============================================================================ */

static void initializeStateTable(StateTableTokenizer* const me) {
    if (me == NULL) return;
    
    /* Initialize all entries to safe defaults */
    for (int state = 0; state < STATE_MAX; state++) {
        for (int event = 0; event < EVENT_MAX; event++) {
            me->stateTable[state][event].nextState = (StateType)state;
            me->stateTable[state][event].actionType = ACTION_NONE;
            me->stateTable[state][event].actionFunc = action_none;
        }
    }
    
    /* STATE_NONUMBER transitions */
    me->stateTable[STATE_NONUMBER][EVENT_DIGIT] = 
        {STATE_GOTNUMBER_WHOLE, ACTION_START_NUMBER, action_start_number};
    me->stateTable[STATE_NONUMBER][EVENT_DOT] = 
        {STATE_GOTNUMBER_FRACTIONAL, ACTION_START_FRACTIONAL, action_start_fractional};
    me->stateTable[STATE_NONUMBER][EVENT_WHITESPACE] = 
        {STATE_NONUMBER, ACTION_NONE, action_none};
    me->stateTable[STATE_NONUMBER][EVENT_END_OF_STRING] = 
        {STATE_NONUMBER, ACTION_NONE, action_none};
    
    /* STATE_GOTNUMBER_WHOLE transitions */
    me->stateTable[STATE_GOTNUMBER_WHOLE][EVENT_DIGIT] = 
        {STATE_GOTNUMBER_WHOLE, ACTION_ADD_DIGIT_WHOLE, action_add_digit_whole};
    me->stateTable[STATE_GOTNUMBER_WHOLE][EVENT_DOT] = 
        {STATE_GOTNUMBER_FRACTIONAL, ACTION_START_FRACTIONAL, action_start_fractional};
    me->stateTable[STATE_GOTNUMBER_WHOLE][EVENT_WHITESPACE] = 
        {STATE_NONUMBER, ACTION_FINISH_NUMBER, action_finish_number};
    me->stateTable[STATE_GOTNUMBER_WHOLE][EVENT_END_OF_STRING] = 
        {STATE_NONUMBER, ACTION_FINISH_NUMBER, action_finish_number};
    
    /* STATE_GOTNUMBER_FRACTIONAL transitions */
    me->stateTable[STATE_GOTNUMBER_FRACTIONAL][EVENT_DIGIT] = 
        {STATE_GOTNUMBER_FRACTIONAL, ACTION_ADD_DIGIT_FRACTIONAL, action_add_digit_fractional};
    me->stateTable[STATE_GOTNUMBER_FRACTIONAL][EVENT_DOT] = 
        {STATE_GOTNUMBER_FRACTIONAL, ACTION_NONE, action_none}; /* Ignore additional dots */
    me->stateTable[STATE_GOTNUMBER_FRACTIONAL][EVENT_WHITESPACE] = 
        {STATE_NONUMBER, ACTION_FINISH_NUMBER, action_finish_number};
    me->stateTable[STATE_GOTNUMBER_FRACTIONAL][EVENT_END_OF_STRING] = 
        {STATE_NONUMBER, ACTION_FINISH_NUMBER, action_finish_number};
}

static void cleanUpRelations(StateTableTokenizer* const me) {
    if (me == NULL || me->context == NULL) return;
    
    /* Note: We don't destroy the mutex here as it might be shared */
    /* The client is responsible for mutex lifecycle management */
    me->context->mutex = NULL;
}
