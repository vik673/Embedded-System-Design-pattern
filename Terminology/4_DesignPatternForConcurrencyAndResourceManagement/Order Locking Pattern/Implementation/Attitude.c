#include "Attitude.h"

void Attitude_Init(Attitude* const me) {
    me->roll = 0.0;
    me->pitch = 0.0;
    me->yaw = 0.0;
}

void Attitude_setAttitude(Attitude* const me, double roll, double pitch, double yaw) {
    me->roll = roll;
    me->pitch = pitch;
    me->yaw = yaw;
}

double Attitude_getRoll(const Attitude* const me) {
    return me->roll;
}

double Attitude_getPitch(const Attitude* const me) {
    return me->pitch;
}

double Attitude_getYaw(const Attitude* const me) {
    return me->yaw;
}
