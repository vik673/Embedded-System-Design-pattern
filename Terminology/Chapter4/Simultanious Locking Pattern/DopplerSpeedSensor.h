#ifndef DopplerSpeedSensor_H
#define DopplerSpeedSensor_H

typedef struct DopplerSpeedSensor {
    short sampleRate;
    int enabled;
} DopplerSpeedSensor;

/* Function declarations */
void DopplerSpeedSensor_configure(DopplerSpeedSensor* const me, short sampleRate);
void DopplerSpeedSensor_disable(DopplerSpeedSensor* const me);
void DopplerSpeedSensor_enable(DopplerSpeedSensor* const me);
double DopplerSpeedSensor_getSpeed(DopplerSpeedSensor* const me);

#endif
