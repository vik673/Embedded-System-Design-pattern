#ifndef TSR_ASYNC_SINGLE_RECEPTOR_H
#define TSR_ASYNC_SINGLE_RECEPTOR_H

#include <stdio.h>
#include "TokenizerAsyncSinglePkg.h"
#include "TSREventQueue.h"

typedef struct TokenizerAsyncSingleReceptor TokenizerAsyncSingleReceptor;

struct TokenizerAsyncSingleReceptor {
    char ch;
    double result;
    TSTATETYPE stateID;
    TSUBSTATETYPE subStateID;
    double tensPlace;
    TSREventQueue* itsTSREventQueue;
};

void TokenizerAsyncSingleReceptor_enter_GotNumber(TokenizerAsyncSingleReceptor* const me);
void TokenizerAsyncSingleReceptor_enter_NoNumber(TokenizerAsyncSingleReceptor* const me);
void TokenizerAsyncSingleReceptor_enter_ProcessingFractionalPart(TokenizerAsyncSingleReceptor* const me);
void TokenizerAsyncSingleReceptor_enter_ProcessingWholePart(TokenizerAsyncSingleReceptor* const me);

void TokenizerAsyncSingleReceptor_exit_GotNumber(TokenizerAsyncSingleReceptor* const me);
void TokenizerAsyncSingleReceptor_exit_NoNumber(TokenizerAsyncSingleReceptor* const me);
void TokenizerAsyncSingleReceptor_exit_ProcessingFractionalPart(TokenizerAsyncSingleReceptor* const me);
void TokenizerAsyncSingleReceptor_exit_ProcessingWholePart(TokenizerAsyncSingleReceptor* const me);

void TokenizerAsyncSingleReceptor_Init(TokenizerAsyncSingleReceptor* const me);
void TokenizerAsyncSingleReceptor_Cleanup(TokenizerAsyncSingleReceptor* const me);

void TokenizerAsyncSingleReceptor_eventDispatch(TokenizerAsyncSingleReceptor* const me, Event e);
void TokenizerAsyncSingleReceptor_taskLoop(TokenizerAsyncSingleReceptor* const me);

TSREventQueue* TokenizerAsyncSingleReceptor_getItsTSREventQueue(const TokenizerAsyncSingleReceptor* const me);
void TokenizerAsyncSingleReceptor_setItsTSREventQueue(TokenizerAsyncSingleReceptor* const me, TSREventQueue* p_TSREventQueue);

TokenizerAsyncSingleReceptor* TokenizerAsyncSingleReceptor_Create(void);
void TokenizerAsyncSingleReceptor_Destroy(TokenizerAsyncSingleReceptor* const me);

#endif
