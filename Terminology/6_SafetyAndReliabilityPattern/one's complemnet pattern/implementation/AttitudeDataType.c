#include "AttitudeDataType.h"
#include <stddef.h>

void AttitudeDataType_Init(AttitudeDataType* const me) {
    if (me != NULL) {
        me->roll = 0;
        me->pitch = 0;
        me->yaw = 0;
    }
}

void AttitudeDataType_Set(AttitudeDataType* const me, int roll, int pitch, int yaw) {
    if (me != NULL) {
        me->roll = roll;
        me->pitch = pitch;
        me->yaw = yaw;
    }
}

void AttitudeDataType_Copy(AttitudeDataType* const dest, const AttitudeDataType* const src) {
    if (dest != NULL && src != NULL) {
        dest->roll = src->roll;
        dest->pitch = src->pitch;
        dest->yaw = src->yaw;
    }
}

int AttitudeDataType_IsEqual(const AttitudeDataType* const a, const AttitudeDataType* const b) {
    if (a == NULL || b == NULL) {
        return 0;
    }
    
    return (a->roll == b->roll && 
            a->pitch == b->pitch && 
            a->yaw == b->yaw) ? 1 : 0;
}
