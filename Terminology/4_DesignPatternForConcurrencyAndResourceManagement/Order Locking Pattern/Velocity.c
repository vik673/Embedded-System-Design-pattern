#include "Velocity.h"

void Velocity_Init(Velocity* const me) {
    me->x = 0.0;
    me->y = 0.0;
    me->z = 0.0;
}

void Velocity_setVelocity(Velocity* const me, double x, double y, double z) {
    me->x = x;
    me->y = y;
    me->z = z;
}

double Velocity_getX(const Velocity* const me) {
    return me->x;
}

double Velocity_getY(const Velocity* const me) {
    return me->y;
}

double Velocity_getZ(const Velocity* const me) {
    return me->z;
}
