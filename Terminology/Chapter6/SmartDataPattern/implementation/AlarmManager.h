#ifndef AlarmManager_H
#define AlarmManager_H

#include "SmartDataExample.h"

typedef struct AlarmManager AlarmManager;
struct AlarmManager {
    ErrorCodeType currentAlarm;
    int alarmCount;
    char alarmMessage[256];
};

/* Constructors and destructors */
void AlarmManager_Init(AlarmManager* const me);
void AlarmManager_Cleanup(AlarmManager* const me);

/* Operations */
void AlarmManager_addAlarm(AlarmManager* const me, ErrorCodeType alarm);
void AlarmManager_clearAlarm(AlarmManager* const me);
ErrorCodeType AlarmManager_getCurrentAlarm(AlarmManager* const me);
int AlarmManager_getAlarmCount(AlarmManager* const me);
char* AlarmManager_getAlarmMessage(AlarmManager* const me);

AlarmManager* AlarmManager_Create(void);
void AlarmManager_Destroy(AlarmManager* const me);

#endif
