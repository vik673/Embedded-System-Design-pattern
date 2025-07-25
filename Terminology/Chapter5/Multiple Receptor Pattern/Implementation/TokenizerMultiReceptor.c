#include "TokenizerMultiReceptor.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Private function to clean up relations
 * @param me Pointer to the tokenizer instance
 */
static void cleanUpRelations(TokenizerMultiReceptor* const me);

/* ============================================================================
 * Constructors and Destructors
 * ============================================================================ */

TokenizerMultiReceptor* TokenizerMultiReceptor_Create(void) {
    TokenizerMultiReceptor* me = (TokenizerMultiReceptor*)malloc(sizeof(TokenizerMultiReceptor));
    if (me != NULL) {
        TokenizerMultiReceptor_Init(me);
    }
    return me;
}

void TokenizerMultiReceptor_Destroy(TokenizerMultiReceptor* const me) {
    if (me != NULL) {
        TokenizerMultiReceptor_Cleanup(me);
        free(me);
    }
}

void TokenizerMultiReceptor_Init(TokenizerMultiReceptor* const me) {
    if (me == NULL) return;
    
    /* Initialize business logic attributes */
    me->ch = '\0';
    me->result = 0.0;
    me->tensPlace = 10.0;
    
    /* Initialize state management attributes */
    me->stateID = NONUMBER_STATE;
    me->subStateID = NULL_SSTATE;
    me->itsMutex = NULL;
    
    printf("TokenizerMultiReceptor initialized\n");
}

void TokenizerMultiReceptor_Cleanup(TokenizerMultiReceptor* const me) {
    if (me != NULL) {
        cleanUpRelations(me);
    }
}

/* ============================================================================
 * Event Receptors - Multiple Event Receptor Pattern Core
 * ============================================================================ */

void TokenizerMultiReceptor_evDigit(TokenizerMultiReceptor* const me, char c) {
    if (me == NULL) return;
    
    if (me->itsMutex != NULL) {
        Mutex_lock(me->itsMutex);
    }
    
    printf("Processing digit: %c\n", c);
    
    switch (me->stateID) {
        case NONUMBER_STATE:
            /* Transition to GotNumber state, default substate */
            TokenizerMultiReceptor_exit_NoNumber(me);
            me->ch = c;
            TokenizerMultiReceptor_enter_GotNumber(me);
            me->stateID = GOTNUMBER_STATE;
            TokenizerMultiReceptor_enter_ProcessingWholePart(me);
            me->subStateID = PROCESSINGWHOLEPART_SSTATE;
            printf("Current value of result: %g\n", me->result);
            break;
            
        case GOTNUMBER_STATE:
            switch (me->subStateID) {
                case PROCESSINGWHOLEPART_SSTATE:
                    TokenizerMultiReceptor_exit_ProcessingWholePart(me);
                    me->ch = c;
                    TokenizerMultiReceptor_enter_ProcessingWholePart(me);
                    printf("Current value of result: %g\n", me->result);
                    break;
                    
                case PROCESSINGFRACTIONALPART_SSTATE:
                    TokenizerMultiReceptor_exit_ProcessingFractionalPart(me);
                    me->ch = c;
                    me->result += digit(me->ch) / me->tensPlace;
                    me->tensPlace *= 10.0;
                    TokenizerMultiReceptor_enter_ProcessingFractionalPart(me);
                    printf("Current value of result: %g\n", me->result);
                    break;
                    
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
    
    if (me->itsMutex != NULL) {
        Mutex_release(me->itsMutex);
    }
}

void TokenizerMultiReceptor_evDot(TokenizerMultiReceptor* const me) {
    if (me == NULL) return;
    
    if (me->itsMutex != NULL) {
        Mutex_lock(me->itsMutex);
    }
    
    printf("Processing dot\n");
    me->ch = '.';
    
    switch (me->stateID) {
        case NONUMBER_STATE:
            /* Transition to GotNumber state, fractional substate */
            TokenizerMultiReceptor_exit_NoNumber(me);
            TokenizerMultiReceptor_enter_GotNumber(me);
            me->stateID = GOTNUMBER_STATE;
            TokenizerMultiReceptor_enter_ProcessingFractionalPart(me);
            me->subStateID = PROCESSINGFRACTIONALPART_SSTATE;
            break;
            
        case GOTNUMBER_STATE:
            switch (me->subStateID) {
                case PROCESSINGWHOLEPART_SSTATE:
                    TokenizerMultiReceptor_exit_ProcessingWholePart(me);
                    TokenizerMultiReceptor_enter_ProcessingFractionalPart(me);
                    me->subStateID = PROCESSINGFRACTIONALPART_SSTATE;
                    break;
                    
                default:
                    /* Ignore dot if already processing fractional part */
                    break;
            }
            break;
            
        default:
            break;
    }
    
    if (me->itsMutex != NULL) {
        Mutex_release(me->itsMutex);
    }
}

void TokenizerMultiReceptor_evEndOfString(TokenizerMultiReceptor* const me) {
    if (me == NULL) return;
    
    if (me->itsMutex != NULL) {
        Mutex_lock(me->itsMutex);
    }
    
    printf("Processing end of string\n");
    
    switch (me->stateID) {
        case GOTNUMBER_STATE:
            switch (me->subStateID) {
                case PROCESSINGWHOLEPART_SSTATE:
                    TokenizerMultiReceptor_exit_ProcessingWholePart(me);
                    break;
                    
                case PROCESSINGFRACTIONALPART_SSTATE:
                    TokenizerMultiReceptor_exit_ProcessingFractionalPart(me);
                    break;
                    
                default:
                    break;
            }
            
            TokenizerMultiReceptor_exit_GotNumber(me);
            printf("Final Number: %g\n", me->result);
            TokenizerMultiReceptor_enter_NoNumber(me);
            me->stateID = NONUMBER_STATE;
            break;
            
        default:
            printf("End of string - no number found\n");
            break;
    }
    
    if (me->itsMutex != NULL) {
        Mutex_release(me->itsMutex);
    }
}

void TokenizerMultiReceptor_evWhiteSpace(TokenizerMultiReceptor* const me) {
    if (me == NULL) return;
    
    if (me->itsMutex != NULL) {
        Mutex_lock(me->itsMutex);
    }
    
    printf("Processing whitespace\n");
    
    switch (me->stateID) {
        case GOTNUMBER_STATE:
            switch (me->subStateID) {
                case PROCESSINGWHOLEPART_SSTATE:
                    TokenizerMultiReceptor_exit_ProcessingWholePart(me);
                    break;
                    
                case PROCESSINGFRACTIONALPART_SSTATE:
                    TokenizerMultiReceptor_exit_ProcessingFractionalPart(me);
                    break;
                    
                default:
                    break;
            }
            
            TokenizerMultiReceptor_exit_GotNumber(me);
            printf("Number: %g\n", me->result);
            TokenizerMultiReceptor_enter_NoNumber(me);
            me->stateID = NONUMBER_STATE;
            break;
            
        default:
            /* Ignore whitespace when not processing a number */
            break;
    }
    
    if (me->itsMutex != NULL) {
        Mutex_release(me->itsMutex);
    }
}

/* ============================================================================
 * State Entry Actions
 * ============================================================================ */

void TokenizerMultiReceptor_enter_GotNumber(TokenizerMultiReceptor* const me) {
    if (me == NULL) return;
    printf("Entering GotNumber state\n");
    me->tensPlace = 10.0;
}

void TokenizerMultiReceptor_enter_NoNumber(TokenizerMultiReceptor* const me) {
    if (me == NULL) return;
    printf("Entering NoNumber state\n");
    me->result = 0.0;
}

void TokenizerMultiReceptor_enter_ProcessingFractionalPart(TokenizerMultiReceptor* const me) {
    if (me == NULL) return;
    printf("Entering ProcessingFractionalPart sub-state\n");
    /* Initialize fractional processing if needed */
}

void TokenizerMultiReceptor_enter_ProcessingWholePart(TokenizerMultiReceptor* const me) {
    if (me == NULL) return;
    printf("Entering ProcessingWholePart sub-state\n");
    me->result = me->result * 10 + digit(me->ch);
}

/* ============================================================================
 * State Exit Actions
 * ============================================================================ */

void TokenizerMultiReceptor_exit_GotNumber(TokenizerMultiReceptor* const me) {
    if (me == NULL) return;
    printf("Exiting GotNumber state\n");
    me->subStateID = NULL_SSTATE;
}

void TokenizerMultiReceptor_exit_NoNumber(TokenizerMultiReceptor* const me) {
    if (me == NULL) return;
    printf("Exiting NoNumber state\n");
    /* No specific cleanup needed */
}

void TokenizerMultiReceptor_exit_ProcessingFractionalPart(TokenizerMultiReceptor* const me) {
    if (me == NULL) return;
    printf("Exiting ProcessingFractionalPart sub-state\n");
    /* No specific cleanup needed */
}

void TokenizerMultiReceptor_exit_ProcessingWholePart(TokenizerMultiReceptor* const me) {
    if (me == NULL) return;
    printf("Exiting ProcessingWholePart sub-state\n");
    /* No specific cleanup needed */
}

/* ============================================================================
 * Accessor Methods
 * ============================================================================ */

Mutex* TokenizerMultiReceptor_getItsMutex(const TokenizerMultiReceptor* const me) {
    if (me == NULL) return NULL;
    return me->itsMutex;
}

void TokenizerMultiReceptor_setItsMutex(TokenizerMultiReceptor* const me, Mutex* p_Mutex) {
    if (me == NULL) return;
    me->itsMutex = p_Mutex;
}

double TokenizerMultiReceptor_getResult(const TokenizerMultiReceptor* const me) {
    if (me == NULL) return 0.0;
    return me->result;
}

TSTATETYPE TokenizerMultiReceptor_getState(const TokenizerMultiReceptor* const me) {
    if (me == NULL) return NULL_STATE;
    return me->stateID;
}

TSUBSTATETYPE TokenizerMultiReceptor_getSubState(const TokenizerMultiReceptor* const me) {
    if (me == NULL) return NULL_SSTATE;
    return me->subStateID;
}

/* ============================================================================
 * Private Helper Functions
 * ============================================================================ */

static void cleanUpRelations(TokenizerMultiReceptor* const me) {
    if (me == NULL) return;
    
    if (me->itsMutex != NULL) {
        /* Note: We don't destroy the mutex here as it might be shared */
        /* The client is responsible for mutex lifecycle management */
        me->itsMutex = NULL;
    }
}
