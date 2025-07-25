#include "BreathingCircuitSensor.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void BreathingCircuitSensor_Init(BreathingCircuitSensor* const me, SensorType type) {
    if (me != NULL) {
        me->sensorType = type;
        me->currentData = 0;
        me->currentState = SENSOR_STATE_NORMAL;
        me->isActive = 1;
        
        /* Initialize with some default values based on sensor type */
        switch (type) {
            case SENSOR_O2_CONCENTRATION:
                me->currentData = 21; /* 21% O2 concentration */
                break;
            case SENSOR_GAS_PRESSURE:
                me->currentData = 15; /* 15 cmH2O pressure */
                break;
            case SENSOR_CIRCUIT_PRESSURE:
                me->currentData = 5; /* 5 cmH2O circuit pressure */
                break;
        }
    }
}

void BreathingCircuitSensor_Cleanup(BreathingCircuitSensor* const me) {
    if (me != NULL) {
        me->isActive = 0;
    }
}

BreathingCircuitSensor* BreathingCircuitSensor_Create(SensorType type) {
    BreathingCircuitSensor* me = (BreathingCircuitSensor*)malloc(sizeof(BreathingCircuitSensor));
    if (me != NULL) {
        BreathingCircuitSensor_Init(me, type);
    }
    return me;
}

void BreathingCircuitSensor_Destroy(BreathingCircuitSensor* const me) {
    if (me != NULL) {
        BreathingCircuitSensor_Cleanup(me);
        free(me);
    }
}

deviceData BreathingCircuitSensor_getData(const BreathingCircuitSensor* const me) {
    if (me != NULL && me->isActive) {
        return me->currentData;
    }
    return -1; /* Error value */
}

unsigned int BreathingCircuitSensor_getState(const BreathingCircuitSensor* const me) {
    if (me != NULL && me->isActive) {
        return (unsigned int)me->currentState;
    }
    return SENSOR_STATE_ERROR;
}

void BreathingCircuitSensor_updateData(BreathingCircuitSensor* const me, deviceData newData) {
    if (me != NULL && me->isActive) {
        me->currentData = newData;
        
        /* Update state based on data thresholds */
        switch (me->sensorType) {
            case SENSOR_O2_CONCENTRATION:
                if (newData < 18 || newData > 24) {
                    me->currentState = SENSOR_STATE_ALARM;
                } else if (newData < 19 || newData > 23) {
                    me->currentState = SENSOR_STATE_WARNING;
                } else {
                    me->currentState = SENSOR_STATE_NORMAL;
                }
                break;
            case SENSOR_GAS_PRESSURE:
                if (newData < 5 || newData > 30) {
                    me->currentState = SENSOR_STATE_ALARM;
                } else if (newData < 8 || newData > 25) {
                    me->currentState = SENSOR_STATE_WARNING;
                } else {
                    me->currentState = SENSOR_STATE_NORMAL;
                }
                break;
            case SENSOR_CIRCUIT_PRESSURE:
                if (newData < 0 || newData > 20) {
                    me->currentState = SENSOR_STATE_ALARM;
                } else if (newData > 15) {
                    me->currentState = SENSOR_STATE_WARNING;
                } else {
                    me->currentState = SENSOR_STATE_NORMAL;
                }
                break;
        }
    }
}

void BreathingCircuitSensor_updateState(BreathingCircuitSensor* const me, SensorState newState) {
    if (me != NULL && me->isActive) {
        me->currentState = newState;
    }
}

void BreathingCircuitSensor_activate(BreathingCircuitSensor* const me) {
    if (me != NULL) {
        me->isActive = 1;
    }
}

void BreathingCircuitSensor_deactivate(BreathingCircuitSensor* const me) {
    if (me != NULL) {
        me->isActive = 0;
    }
}

void BreathingCircuitSensor_simulateReading(BreathingCircuitSensor* const me) {
    if (me != NULL && me->isActive) {
        static int initialized = 0;
        if (!initialized) {
            srand((unsigned int)time(NULL));
            initialized = 1;
        }
        
        deviceData newData;
        
        /* Simulate sensor readings with some random variation */
        switch (me->sensorType) {
            case SENSOR_O2_CONCENTRATION:
                /* Simulate O2 concentration between 20-22% with small variations */
                newData = 20 + (rand() % 3);
                break;
            case SENSOR_GAS_PRESSURE:
                /* Simulate gas pressure between 12-18 cmH2O */
                newData = 12 + (rand() % 7);
                break;
            case SENSOR_CIRCUIT_PRESSURE:
                /* Simulate circuit pressure between 3-8 cmH2O */
                newData = 3 + (rand() % 6);
                break;
        }
        
        BreathingCircuitSensor_updateData(me, newData);
    }
}
