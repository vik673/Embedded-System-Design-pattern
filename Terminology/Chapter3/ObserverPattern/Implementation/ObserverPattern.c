#include "ObserverPattern.h"
#include <string.h>
#include <time.h>

// ==================== GasSensor Implementation (ConcreteSubject) ====================

GasSensor* GasSensor_create(void) {
    GasSensor* me = (GasSensor*)malloc(sizeof(GasSensor));
    if (me != NULL) {
        me->itsGasData = (GasData*)malloc(sizeof(GasData));
        me->subscriberCount = 0;
        
        // Initialize gas data
        if (me->itsGasData != NULL) {
            me->itsGasData->concentration = 0.0f;
            me->itsGasData->sensorId = 1;
            me->itsGasData->timestamp = 0;
        }
        
        // Initialize notification handles array
        for (int i = 0; i < MAX_SUBSCRIBERS; i++) {
            me->itsGasNH[i] = NULL;
        }
    }
    return me;
}

void GasSensor_destroy(GasSensor* me) {
    if (me != NULL) {
        if (me->itsGasData != NULL) {
            free(me->itsGasData);
        }
        
        // Free notification handles
        for (int i = 0; i < me->subscriberCount; i++) {
            if (me->itsGasNH[i] != NULL) {
                free(me->itsGasNH[i]);
            }
        }
        
        free(me);
    }
}

int GasSensor_subscribe(GasSensor* me, void (*acceptorPtr)(void*, GasData*), void* instancePtr) {
    if (me == NULL || acceptorPtr == NULL) {
        return -1; // Invalid parameters
    }
    
    if (me->subscriberCount >= MAX_SUBSCRIBERS) {
        return -2; // Maximum subscribers reached
    }
    
    // Check if already subscribed
    for (int i = 0; i < me->subscriberCount; i++) {
        if (me->itsGasNH[i] != NULL && 
            me->itsGasNH[i]->acceptorPtr == acceptorPtr && 
            me->itsGasNH[i]->instancePtr == instancePtr) {
            return -3; // Already subscribed
        }
    }
    
    // Create new notification handle
    GasNotificationHandle* handle = (GasNotificationHandle*)malloc(sizeof(GasNotificationHandle));
    if (handle == NULL) {
        return -4; // Memory allocation failed
    }
    
    handle->acceptorPtr = acceptorPtr;
    handle->instancePtr = instancePtr;
    
    me->itsGasNH[me->subscriberCount] = handle;
    me->subscriberCount++;
    
    printf("Subscriber added successfully. Total subscribers: %d\n", me->subscriberCount);
    return 0; // Success
}

int GasSensor_unsubscribe(GasSensor* me, void (*acceptorPtr)(void*, GasData*)) {
    if (me == NULL || acceptorPtr == NULL) {
        return -1; // Invalid parameters
    }
    
    // Find and remove the subscriber
    for (int i = 0; i < me->subscriberCount; i++) {
        if (me->itsGasNH[i] != NULL && me->itsGasNH[i]->acceptorPtr == acceptorPtr) {
            // Free the notification handle
            free(me->itsGasNH[i]);
            
            // Shift remaining elements
            for (int j = i; j < me->subscriberCount - 1; j++) {
                me->itsGasNH[j] = me->itsGasNH[j + 1];
            }
            
            me->itsGasNH[me->subscriberCount - 1] = NULL;
            me->subscriberCount--;
            
            printf("Subscriber removed successfully. Total subscribers: %d\n", me->subscriberCount);
            return 0; // Success
        }
    }
    
    return -2; // Subscriber not found
}

void GasSensor_notify(GasSensor* me) {
    if (me == NULL || me->itsGasData == NULL) {
        return;
    }
    
    printf("Notifying %d subscribers...\n", me->subscriberCount);
    
    // Walk through the list of subscribers and notify each one
    for (int pos = 0; pos < me->subscriberCount; pos++) {
        if (me->itsGasNH[pos] != NULL && me->itsGasNH[pos]->acceptorPtr != NULL) {
            // Call the accept function as described in the text:
            // me->itsGasNH[pos]->acceptorPtr(me->itsGasNH[pos]->instancePtr, me->itsGasData);
            me->itsGasNH[pos]->acceptorPtr(me->itsGasNH[pos]->instancePtr, me->itsGasData);
        }
    }
}

void GasSensor_newData(GasSensor* me, float concentration, int sensorId) {
    if (me == NULL || me->itsGasData == NULL) {
        return;
    }
    
    // Update gas data
    me->itsGasData->concentration = concentration;
    me->itsGasData->sensorId = sensorId;
    me->itsGasData->timestamp = time(NULL);
    
    printf("New gas data received: Concentration=%.2f ppm, SensorID=%d\n", 
           concentration, sensorId);
    
    // Notify all subscribers
    GasSensor_notify(me);
}

void GasSensor_dumpList(GasSensor* me) {
    if (me == NULL) {
        return;
    }
    
    printf("=== Gas Sensor Subscriber List ===\n");
    printf("Total subscribers: %d\n", me->subscriberCount);
    
    for (int i = 0; i < me->subscriberCount; i++) {
        if (me->itsGasNH[i] != NULL) {
            printf("Subscriber %d: Function=0x%p, Instance=0x%p\n", 
                   i + 1, 
                   (void*)me->itsGasNH[i]->acceptorPtr, 
                   me->itsGasNH[i]->instancePtr);
        }
    }
    printf("==================================\n");
}

// ==================== DisplayMonitor Implementation (ConcreteClient) ====================

DisplayMonitor* DisplayMonitor_create(int id, const char* name) {
    DisplayMonitor* me = (DisplayMonitor*)malloc(sizeof(DisplayMonitor));
    if (me != NULL) {
        me->displayId = id;
        strncpy(me->name, name, sizeof(me->name) - 1);
        me->name[sizeof(me->name) - 1] = '\0'; // Ensure null termination
    }
    return me;
}

void DisplayMonitor_destroy(DisplayMonitor* me) {
    if (me != NULL) {
        free(me);
    }
}

void DisplayMonitor_accept(void* me, GasData* gasData) {
    DisplayMonitor* self = (DisplayMonitor*)me;
    if (self != NULL && gasData != NULL) {
        printf("[DISPLAY %s] Gas Alert: %.2f ppm from Sensor %d at timestamp %ld\n",
               self->name, gasData->concentration, gasData->sensorId, gasData->timestamp);
    }
}

// ==================== AlarmSystem Implementation (ConcreteClient) ====================

AlarmSystem* AlarmSystem_create(int id, float threshold) {
    AlarmSystem* me = (AlarmSystem*)malloc(sizeof(AlarmSystem));
    if (me != NULL) {
        me->alarmId = id;
        me->threshold = threshold;
        me->isActive = 0; // Initially inactive
    }
    return me;
}

void AlarmSystem_destroy(AlarmSystem* me) {
    if (me != NULL) {
        free(me);
    }
}

void AlarmSystem_accept(void* me, GasData* gasData) {
    AlarmSystem* self = (AlarmSystem*)me;
    if (self != NULL && gasData != NULL) {
        if (gasData->concentration > self->threshold) {
            if (!self->isActive) {
                self->isActive = 1;
                printf("[ALARM %d] *** DANGER *** Gas concentration %.2f ppm exceeds threshold %.2f ppm!\n",
                       self->alarmId, gasData->concentration, self->threshold);
            }
        } else {
            if (self->isActive) {
                self->isActive = 0;
                printf("[ALARM %d] All clear - Gas concentration %.2f ppm is below threshold %.2f ppm\n",
                       self->alarmId, gasData->concentration, self->threshold);
            }
        }
    }
}

// ==================== DataLogger Implementation (ConcreteClient) ====================

DataLogger* DataLogger_create(int id, const char* filename) {
    DataLogger* me = (DataLogger*)malloc(sizeof(DataLogger));
    if (me != NULL) {
        me->loggerId = id;
        me->logFile = fopen(filename, "a"); // Open in append mode
        if (me->logFile == NULL) {
            printf("Warning: Could not open log file %s\n", filename);
        }
    }
    return me;
}

void DataLogger_destroy(DataLogger* me) {
    if (me != NULL) {
        if (me->logFile != NULL) {
            fclose(me->logFile);
        }
        free(me);
    }
}

void DataLogger_accept(void* me, GasData* gasData) {
    DataLogger* self = (DataLogger*)me;
    if (self != NULL && gasData != NULL) {
        printf("[LOGGER %d] Logging gas data: %.2f ppm\n", self->loggerId, gasData->concentration);
        
        if (self->logFile != NULL) {
            fprintf(self->logFile, "%ld,%d,%.2f\n", 
                    gasData->timestamp, gasData->sensorId, gasData->concentration);
            fflush(self->logFile); // Ensure data is written immediately
        }
    }
}
