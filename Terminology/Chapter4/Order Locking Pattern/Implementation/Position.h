#ifndef POSITION_H
#define POSITION_H

typedef struct Position Position;

struct Position {
    double latitude;
    double longitude;
    double altitude;
};

/* Constructor */
void Position_Init(Position* const me);

/* Operations */
void Position_setPosition(Position* const me, double lat, double lon, double alt);
double Position_getLatitude(const Position* const me);
double Position_getLongitude(const Position* const me);
double Position_getAltitude(const Position* const me);

#endif /* POSITION_H */
