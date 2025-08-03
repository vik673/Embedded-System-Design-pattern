#include "CRDisplay.h"
#include <stdio.h>
#include <stdlib.h>

void CRDisplay_Init(CRDisplay* const me) {
    me->displayId = 1;
}

void CRDisplay_Cleanup(CRDisplay* const me) {
    // Cleanup display resources if needed
}

CRDisplay* CRDisplay_Create(void) {
    CRDisplay* me = (CRDisplay*)malloc(sizeof(CRDisplay));
    if(me != NULL) {
        CRDisplay_Init(me);
    }
    return me;
}

void CRDisplay_Destroy(CRDisplay* const me) {
    if(me != NULL) {
        CRDisplay_Cleanup(me);
        free(me);
    }
}

void CRDisplay_printMsg(CRDisplay* const me, const char* message) {
    printf("Display %d: %s\n", me->displayId, message);
}

void CRDisplay_printInt(CRDisplay* const me, const char* prefix, int value) {
    printf("Display %d: %s%d\n", me->displayId, prefix, value);
}
