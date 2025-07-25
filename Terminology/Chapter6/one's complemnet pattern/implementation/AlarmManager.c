#include "AlarmManager.h"
#include <stdlib.h>
#include <stdio.h>

void AlarmManager_Init(AlarmManager* const me) {
    if (me != NULL) {
        me->alarmCount = 0;
        me->maxAlarms = 10;
        
        // Initialize all alarm slots to 0
        for (int i = 0; i < me->maxAlarms; i++) {
            me->activeAlarms[i] = 0;
        }
    }
}

void AlarmManager_Cleanup(AlarmManager* const me) {
    if (me != NULL) {
        AlarmManager_clearAllAlarms(me);
    }
}

int AlarmManager_addAlarm(AlarmManager* const me, int alarmCode) {
    if (me == NULL || me->alarmCount >= me->maxAlarms) {
        return 0; // Failed to add alarm
    }
    
    // Check if alarm already exists
    if (AlarmManager_isAlarmActive(me, alarmCode)) {
        return 1; // Alarm already exists, consider it success
    }
    
    // Add new alarm
    me->activeAlarms[me->alarmCount] = alarmCode;
    me->alarmCount++;
    
    // Log the alarm (in a real system, this might write to a log file or notify operators)
    printf("ALARM TRIGGERED: Code 0x%X - ", alarmCode);
    switch (alarmCode) {
        case ATTITUDE_MEMORY_FAULT:
            printf("Attitude Memory Corruption Detected\n");
            break;
        case GENERAL_SYSTEM_ERROR:
            printf("General System Error\n");
            break;
        case SENSOR_FAULT:
            printf("Sensor Fault Detected\n");
            break;
        default:
            printf("Unknown Alarm\n");
            break;
    }
    
    return 1; // Success
}

int AlarmManager_removeAlarm(AlarmManager* const me, int alarmCode) {
    if (me == NULL || me->alarmCount == 0) {
        return 0; // Failed to remove alarm
    }
    
    // Find and remove the alarm
    for (int i = 0; i < me->alarmCount; i++) {
        if (me->activeAlarms[i] == alarmCode) {
            // Shift remaining alarms down
            for (int j = i; j < me->alarmCount - 1; j++) {
                me->activeAlarms[j] = me->activeAlarms[j + 1];
            }
            me->alarmCount--;
            me->activeAlarms[me->alarmCount] = 0; // Clear the last slot
            
            printf("ALARM CLEARED: Code 0x%X\n", alarmCode);
            return 1; // Success
        }
    }
    
    return 0; // Alarm not found
}

int AlarmManager_isAlarmActive(const AlarmManager* const me, int alarmCode) {
    if (me == NULL) {
        return 0;
    }
    
    for (int i = 0; i < me->alarmCount; i++) {
        if (me->activeAlarms[i] == alarmCode) {
            return 1; // Alarm is active
        }
    }
    
    return 0; // Alarm not found
}

int AlarmManager_getAlarmCount(const AlarmManager* const me) {
    if (me == NULL) {
        return 0;
    }
    return me->alarmCount;
}

void AlarmManager_clearAllAlarms(AlarmManager* const me) {
    if (me != NULL) {
        for (int i = 0; i < me->maxAlarms; i++) {
            me->activeAlarms[i] = 0;
        }
        me->alarmCount = 0;
        printf("All alarms cleared\n");
    }
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
