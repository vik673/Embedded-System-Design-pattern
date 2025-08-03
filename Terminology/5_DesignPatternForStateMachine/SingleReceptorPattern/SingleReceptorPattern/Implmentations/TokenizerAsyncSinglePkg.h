#ifndef TOKENIZER_ASYNC_SINGLE_PKG_H
#define TOKENIZER_ASYNC_SINGLE_PKG_H

#include "TokenizerCommonPkg.h"

/*
OS signal and wait functions for
task synchronization
*/
void postSignal(void);
void waitOnSignal(void);

#endif
