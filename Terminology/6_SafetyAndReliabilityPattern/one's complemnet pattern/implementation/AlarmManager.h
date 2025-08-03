#ifndef AlarmManager_H
#define AlarmManager_H

/**
 * AlarmManager - Manages system alarms and notifications
 * Used by the One's Complement Pattern to report memory corruption
 */

// Alarm codes
#define ATTITUDE_MEMORY_FAULT 0x1001
#define GENERAL_SYSTEM_ERROR  0x1002
#define SENSOR_FAULT         0x1003

typedef struct AlarmManager AlarmManager;
struct AlarmManager {
    int activeAlarms[10];  // Array to store active alarm codes
    int alarmCount;        // Number of active alarms
    int maxAlarms;         // Maximum number of alarms
};

/**
 * Initialize the AlarmManager
 * @param me Pointer to the AlarmManager to initialize
 */
void AlarmManager_Init(AlarmManager* const me);

/**
 * Cleanup the AlarmManager
 * @param me Pointer to the AlarmManager to cleanup
 */
void AlarmManager_Cleanup(AlarmManager* const me);

/**
 * Add an alarm to the manager
 * @param me Pointer to the AlarmManager
 * @param alarmCode The alarm code to add
 * @return 1 if successfully added, 0 if failed
 */
int AlarmManager_addAlarm(AlarmManager* const me, int alarmCode);

/**
 * Remove an alarm from the manager
 * @param me Pointer to the AlarmManager
 * @param alarmCode The alarm code to remove
 * @return 1 if successfully removed, 0 if not found
 */
int AlarmManager_removeAlarm(AlarmManager* const me, int alarmCode);

/**
 * Check if a specific alarm is active
 * @param me Pointer to the AlarmManager
 * @param alarmCode The alarm code to check
 * @return 1 if alarm is active, 0 if not
 */
int AlarmManager_isAlarmActive(const AlarmManager* const me, int alarmCode);

/**
 * Get the number of active alarms
 * @param me Pointer to the AlarmManager
 * @return Number of active alarms
 */
int AlarmManager_getAlarmCount(const AlarmManager* const me);

/**
 * Clear all alarms
 * @param me Pointer to the AlarmManager
 */
void AlarmManager_clearAllAlarms(AlarmManager* const me);

/**
 * Create a new AlarmManager instance
 * @return Pointer to the created AlarmManager, NULL if creation failed
 */
AlarmManager* AlarmManager_Create(void);

/**
 * Destroy an AlarmManager instance
 * @param me Pointer to the AlarmManager to destroy
 */
void AlarmManager_Destroy(AlarmManager* const me);

#endif /* AlarmManager_H */
