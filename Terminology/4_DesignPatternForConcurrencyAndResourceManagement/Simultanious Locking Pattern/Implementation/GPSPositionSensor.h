#ifndef GPSPositionSensor_H
#define GPSPositionSensor_H

#include "Position.h"

typedef struct GPSPositionSensor {
    short requiredSatellites;
    int useFastMode;
    int active;
} GPSPositionSensor;

/* Function declarations */
void GPSPositionSensor_activate(GPSPositionSensor* const me);
void GPSPositionSensor_configure(GPSPositionSensor* const me, short reqSatellites, int useFast);
void GPSPositionSensor_deactivate(GPSPositionSensor* const me);
Position GPSPositionSensor_getPosition(GPSPositionSensor* const me);

#endif
