#ifndef BreathingCircuitSensor_H
#define BreathingCircuitSensor_H

typedef int deviceData;

typedef enum {
    SENSOR_O2_CONCENTRATION = 0,
    SENSOR_GAS_PRESSURE = 1,
    SENSOR_CIRCUIT_PRESSURE = 2
} SensorType;

typedef enum {
    SENSOR_STATE_NORMAL = 0,
    SENSOR_STATE_WARNING = 1,
    SENSOR_STATE_ALARM = 2,
    SENSOR_STATE_ERROR = 3
} SensorState;

typedef struct BreathingCircuitSensor BreathingCircuitSensor;
struct BreathingCircuitSensor {
    SensorType sensorType;
    deviceData currentData;
    SensorState currentState;
    int isActive;
};

/* Constructor and Destructor */
void BreathingCircuitSensor_Init(BreathingCircuitSensor* const me, SensorType type);
void BreathingCircuitSensor_Cleanup(BreathingCircuitSensor* const me);
BreathingCircuitSensor* BreathingCircuitSensor_Create(SensorType type);
void BreathingCircuitSensor_Destroy(BreathingCircuitSensor* const me);

/* Operations */
deviceData BreathingCircuitSensor_getData(const BreathingCircuitSensor* const me);
unsigned int BreathingCircuitSensor_getState(const BreathingCircuitSensor* const me);
void BreathingCircuitSensor_updateData(BreathingCircuitSensor* const me, deviceData newData);
void BreathingCircuitSensor_updateState(BreathingCircuitSensor* const me, SensorState newState);
void BreathingCircuitSensor_activate(BreathingCircuitSensor* const me);
void BreathingCircuitSensor_deactivate(BreathingCircuitSensor* const me);

/* Simulation functions */
void BreathingCircuitSensor_simulateReading(BreathingCircuitSensor* const me);

#endif
