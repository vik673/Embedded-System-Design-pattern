#include "UserInput.h"
#include <stdlib.h>
#include <stdio.h>

void UserInput_Init(UserInput* const me) {
    me->x = 0;
    me->y = 0;
    me->z = 0;
    me->inputReady = 0;
}

void UserInput_Cleanup(UserInput* const me) {
    // Cleanup input resources if needed
}

UserInput* UserInput_Create(void) {
    UserInput* me = (UserInput*)malloc(sizeof(UserInput));
    if(me != NULL) {
        UserInput_Init(me);
    }
    return me;
}

void UserInput_Destroy(UserInput* const me) {
    if(me != NULL) {
        UserInput_Cleanup(me);
        free(me);
    }
}

int UserInput_getX(const UserInput* const me) {
    return me->x;
}

int UserInput_getY(const UserInput* const me) {
    return me->y;
}

int UserInput_getZ(const UserInput* const me) {
    return me->z;
}

void UserInput_setCoordinates(UserInput* const me, int x, int y, int z) {
    me->x = x;
    me->y = y;
    me->z = z;
    me->inputReady = 1;
}

int UserInput_isInputReady(const UserInput* const me) {
    return me->inputReady;
}
