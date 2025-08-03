#ifndef VELOCITY_H
#define VELOCITY_H

typedef struct Velocity Velocity;

struct Velocity {
    double x;
    double y;
    double z;
};

/* Constructor */
void Velocity_Init(Velocity* const me);

/* Operations */
void Velocity_setVelocity(Velocity* const me, double x, double y, double z);
double Velocity_getX(const Velocity* const me);
double Velocity_getY(const Velocity* const me);
double Velocity_getZ(const Velocity* const me);

#endif /* VELOCITY_H */
