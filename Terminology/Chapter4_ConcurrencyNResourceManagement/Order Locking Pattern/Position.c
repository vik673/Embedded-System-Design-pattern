#include "Position.h"

void Position_Init(Position* const me) {
    me->latitude = 0.0;
    me->longitude = 0.0;
    me->altitude = 0.0;
}

void Position_setPosition(Position* const me, double lat, double lon, double alt) {
    me->latitude = lat;
    me->longitude = lon;
    me->altitude = alt;
}

double Position_getLatitude(const Position* const me) {
    return me->latitude;
}

double Position_getLongitude(const Position* const me) {
    return me->longitude;
}

double Position_getAltitude(const Position* const me) {
    return me->altitude;
}
