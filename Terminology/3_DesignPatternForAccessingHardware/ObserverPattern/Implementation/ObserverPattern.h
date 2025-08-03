#ifndef OBSERVER_PATTERN_H
#define OBSERVER_PATTERN_H

#include <stdio.h>
#include <stdlib.h>

// Forward declarations
typedef struct GasSensor GasSensor;
typedef struct GasNotificationHandle GasNotificationHandle;
typedef struct GasData GasData;

// Maximum number of subscribers
#define MAX_SUBSCRIBERS 10

// Gas data structure - the Datum in the pattern
typedef struct GasData {
    float concentration;    // Gas concentration in ppm
    int sensorId;          // Sensor identifier
    long timestamp;        // Timestamp of reading
} GasData;

// Notification Handle - contains function pointer and instance data
typedef struct GasNotificationHandle {
    void (*acceptorPtr)(void* instancePtr, GasData* gasData);  // Function pointer
    void* instancePtr;                                         // Instance data pointer
} GasNotificationHandle;

// Abstract Subject Interface - GasSensor (ConcreteSubject)
typedef struct GasSensor {
    GasData* itsGasData;                                      // Current gas data
    GasNotificationHandle* itsGasNH[MAX_SUBSCRIBERS];         // Array of notification handles
    int subscriberCount;                                      // Current number of subscribers
} GasSensor;

// Function prototypes for GasSensor (ConcreteSubject)
GasSensor* GasSensor_create(void);
void GasSensor_destroy(GasSensor* me);
int GasSensor_subscribe(GasSensor* me, void (*acceptorPtr)(void*, GasData*), void* instancePtr);
int GasSensor_unsubscribe(GasSensor* me, void (*acceptorPtr)(void*, GasData*));
void GasSensor_notify(GasSensor* me);
void GasSensor_newData(GasSensor* me, float concentration, int sensorId);
void GasSensor_dumpList(GasSensor* me);

// Abstract Client Interface
typedef struct AbstractClient {
    void (*accept)(void* me, GasData* gasData);
} AbstractClient;

// Concrete Client 1 - Display Monitor
typedef struct DisplayMonitor {
    int displayId;
    char name[50];
} DisplayMonitor;

DisplayMonitor* DisplayMonitor_create(int id, const char* name);
void DisplayMonitor_destroy(DisplayMonitor* me);
void DisplayMonitor_accept(void* me, GasData* gasData);

// Concrete Client 2 - Alarm System
typedef struct AlarmSystem {
    int alarmId;
    float threshold;
    int isActive;
} AlarmSystem;

AlarmSystem* AlarmSystem_create(int id, float threshold);
void AlarmSystem_destroy(AlarmSystem* me);
void AlarmSystem_accept(void* me, GasData* gasData);

// Concrete Client 3 - Data Logger
typedef struct DataLogger {
    int loggerId;
    FILE* logFile;
} DataLogger;

DataLogger* DataLogger_create(int id, const char* filename);
void DataLogger_destroy(DataLogger* me);
void DataLogger_accept(void* me, GasData* gasData);

#endif // OBSERVER_PATTERN_H
