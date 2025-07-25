#include "TSRAsyncSingleReceptor.h"
#include <stdlib.h>

static void cleanUpRelations(TokenizerAsyncSingleReceptor* const me);

void TokenizerAsyncSingleReceptor_enter_GotNumber(TokenizerAsyncSingleReceptor* const me) {
    me->tensPlace = 10.0;
}

void TokenizerAsyncSingleReceptor_enter_NoNumber(TokenizerAsyncSingleReceptor* const me) {
    me->result = 0.0;
}

void TokenizerAsyncSingleReceptor_enter_ProcessingFractionalPart(TokenizerAsyncSingleReceptor* const me) {
    /* enter appropriate actions, if any here */
}

void TokenizerAsyncSingleReceptor_enter_ProcessingWholePart(TokenizerAsyncSingleReceptor* const me) {
    me->result = me->result * 10 + digit(me->ch);
}

void TokenizerAsyncSingleReceptor_exit_GotNumber(TokenizerAsyncSingleReceptor* const me) {
    me->subStateID = NULL_SSTATE;
}

void TokenizerAsyncSingleReceptor_exit_NoNumber(TokenizerAsyncSingleReceptor* const me) {
    /* enter appropriate actions, if any here */
}

void TokenizerAsyncSingleReceptor_exit_ProcessingFractionalPart(TokenizerAsyncSingleReceptor* const me) {
    /* enter appropriate actions, if any here */
}

void TokenizerAsyncSingleReceptor_exit_ProcessingWholePart(TokenizerAsyncSingleReceptor* const me) {
    /* enter appropriate actions, if any here */
}

void TokenizerAsyncSingleReceptor_Init(TokenizerAsyncSingleReceptor* const me) {
    me->ch = 'x';
    me->result = 0.0;
    me->tensPlace = 10.0;
    me->itsTSREventQueue = NULL;
    me->stateID = NONUMBER_STATE;
    me->subStateID = NULL_SSTATE;
}

void TokenizerAsyncSingleReceptor_taskLoop(TokenizerAsyncSingleReceptor* const me) {
    while (1) {
        waitOnSignal(); /* wait until event occurs */
        
        while (!TSREventQueue_isEmpty(me->itsTSREventQueue)) {
            TokenizerAsyncSingleReceptor_eventDispatch(me,
                TSREventQueue_pull(me->itsTSREventQueue));
        }
    }
}

void TokenizerAsyncSingleReceptor_eventDispatch(TokenizerAsyncSingleReceptor* const me, Event e) {
    switch (e.eType) {
        case EVDIGIT:
            switch (me->stateID) {
                case NONUMBER_STATE:
                    /* transition to GotNumber state, default substate */
                    TokenizerAsyncSingleReceptor_exit_NoNumber(me);
                    me->ch = e.ed.c;
                    TokenizerAsyncSingleReceptor_enter_GotNumber(me);
                    me->stateID = GOTNUMBER_STATE;
                    TokenizerAsyncSingleReceptor_enter_ProcessingWholePart(me);
                    me->subStateID = PROCESSINGWHOLEPART_SSTATE;
                    printf("Current value of result: %g\n", me->result);
                    break;
                    
                case GOTNUMBER_STATE:
                    switch (me->subStateID) {
                        case PROCESSINGWHOLEPART_SSTATE:
                            TokenizerAsyncSingleReceptor_exit_ProcessingWholePart(me);
                            me->ch = e.ed.c;
                            TokenizerAsyncSingleReceptor_enter_ProcessingWholePart(me);
                            printf("Current value of result: %g\n", me->result);
                            break;
                            
                        case PROCESSINGFRACTIONALPART_SSTATE:
                            TokenizerAsyncSingleReceptor_exit_ProcessingFractionalPart(me);
                            me->ch = e.ed.c;
                            me->result += digit(me->ch) / me->tensPlace;
                            me->tensPlace *= 10.0;
                            TokenizerAsyncSingleReceptor_enter_ProcessingFractionalPart(me);
                            printf("Current value of result: %g\n", me->result);
                            break;
                    }
                    break;
            }
            break;
            
        case EVDOT:
            me->ch = '.';
            switch (me->stateID) {
                case NONUMBER_STATE:
                    /* transition to GotNumber state, default substate */
                    TokenizerAsyncSingleReceptor_exit_NoNumber(me);
                    TokenizerAsyncSingleReceptor_enter_GotNumber(me);
                    me->stateID = GOTNUMBER_STATE;
                    TokenizerAsyncSingleReceptor_enter_ProcessingFractionalPart(me);
                    me->subStateID = PROCESSINGFRACTIONALPART_SSTATE;
                    break;
                    
                case GOTNUMBER_STATE:
                    switch (me->subStateID) {
                        case PROCESSINGWHOLEPART_SSTATE:
                            TokenizerAsyncSingleReceptor_exit_ProcessingWholePart(me);
                            TokenizerAsyncSingleReceptor_enter_ProcessingFractionalPart(me);
                            me->subStateID = PROCESSINGFRACTIONALPART_SSTATE;
                            break;
                    }
                    break;
            }
            break;
            
        case EVWHITESPACE:
        case EVENDOFSTRING:
            switch (me->stateID) {
                case GOTNUMBER_STATE:
                    switch (me->subStateID) {
                        case PROCESSINGWHOLEPART_SSTATE:
                            TokenizerAsyncSingleReceptor_exit_ProcessingWholePart(me);
                            break;
                            
                        case PROCESSINGFRACTIONALPART_SSTATE:
                            TokenizerAsyncSingleReceptor_exit_ProcessingFractionalPart(me);
                            break;
                    }
                    TokenizerAsyncSingleReceptor_exit_GotNumber(me);
                    printf("Number: %g\n", me->result);
                    TokenizerAsyncSingleReceptor_enter_NoNumber(me);
                    me->stateID = NONUMBER_STATE;
                    break;
            }
            break;
    } // end switch e.eType
}

TSREventQueue* TokenizerAsyncSingleReceptor_getItsTSREventQueue(const TokenizerAsyncSingleReceptor* const me) {
    return me->itsTSREventQueue;
}

void TokenizerAsyncSingleReceptor_setItsTSREventQueue(TokenizerAsyncSingleReceptor* const me, TSREventQueue* p_TSREventQueue) {
    me->itsTSREventQueue = p_TSREventQueue;
}

TokenizerAsyncSingleReceptor* TokenizerAsyncSingleReceptor_Create(void) {
    TokenizerAsyncSingleReceptor* me = (TokenizerAsyncSingleReceptor*)malloc(sizeof(TokenizerAsyncSingleReceptor));
    if (me != NULL) {
        TokenizerAsyncSingleReceptor_Init(me);
    }
    return me;
}

void TokenizerAsyncSingleReceptor_Destroy(TokenizerAsyncSingleReceptor* const me) {
    if (me != NULL) {
        TokenizerAsyncSingleReceptor_Cleanup(me);
        free(me);
    }
}

static void cleanUpRelations(TokenizerAsyncSingleReceptor* const me) {
    if (me->itsTSREventQueue != NULL) {
        me->itsTSREventQueue = NULL;
    }
}

void TokenizerAsyncSingleReceptor_Cleanup(TokenizerAsyncSingleReceptor* const me) {
    cleanUpRelations(me);
}
