#ifndef OpticalSpeedSensor_H
#define OpticalSpeedSensor_H

typedef struct OpticalSpeedSensor {
    int wheelSize;
    int sensitivity;
    int enabled;
} OpticalSpeedSensor;

/* Function declarations */
void OpticalSpeedSensor_configure(OpticalSpeedSensor* const me, int wheelSize, int sensitivity);
void OpticalSpeedSensor_disable(OpticalSpeedSensor* const me);
void OpticalSpeedSensor_enable(OpticalSpeedSensor* const me);
double OpticalSpeedSensor_getSpeed(OpticalSpeedSensor* const me);

#endif
