#include "AlarmManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void AlarmManager_Init(AlarmManager* const me) {
    me->currentAlarm = NO_ERRORS;
    me->alarmCount = 0;
    strcpy(me->alarmMessage, "No alarms");
}

void AlarmManager_Cleanup(AlarmManager* const me) {
    /* Nothing to clean up in this simple implementation */
}

void AlarmManager_addAlarm(AlarmManager* const me, ErrorCodeType alarm) {
    if (me != NULL) {
        me->currentAlarm = alarm;
        me->alarmCount++;
        
        switch (alarm) {
            case BELOW_RANGE:
                strcpy(me->alarmMessage, "Value below acceptable range");
                break;
            case ABOVE_RANGE:
                strcpy(me->alarmMessage, "Value above acceptable range");
                break;
            case INCONSISTENT_VALUE:
                strcpy(me->alarmMessage, "Inconsistent value detected");
                break;
            case ILLEGAL_USE_OF_NULL_PTR:
                strcpy(me->alarmMessage, "Illegal use of null pointer");
                break;
            case INDEX_OUT_OF_RANGE:
                strcpy(me->alarmMessage, "Index out of range");
                break;
            default:
                strcpy(me->alarmMessage, "Unknown error");
                break;
        }
        
        printf("ALARM: %s (Count: %d)\n", me->alarmMessage, me->alarmCount);
    }
}

void AlarmManager_clearAlarm(AlarmManager* const me) {
    if (me != NULL) {
        me->currentAlarm = NO_ERRORS;
        strcpy(me->alarmMessage, "No alarms");
    }
}

ErrorCodeType AlarmManager_getCurrentAlarm(AlarmManager* const me) {
    return (me != NULL) ? me->currentAlarm : ILLEGAL_USE_OF_NULL_PTR;
}

int AlarmManager_getAlarmCount(AlarmManager* const me) {
    return (me != NULL) ? me->alarmCount : -1;
}

char* AlarmManager_getAlarmMessage(AlarmManager* const me) {
    return (me != NULL) ? me->alarmMessage : NULL;
}

AlarmManager* AlarmManager_Create(void) {
    AlarmManager* me = (AlarmManager*)malloc(sizeof(AlarmManager));
    if (me != NULL) {
        AlarmManager_Init(me);
    }
    return me;
}

void AlarmManager_Destroy(AlarmManager* const me) {
    if (me != NULL) {
        AlarmManager_Cleanup(me);
        free(me);
    }
}
