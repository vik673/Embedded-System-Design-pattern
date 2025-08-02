#ifndef ATTITUDE_H
#define ATTITUDE_H

typedef struct Attitude Attitude;

struct Attitude {
    double roll;
    double pitch;
    double yaw;
};

/* Constructor */
void Attitude_Init(Attitude* const me);

/* Operations */
void Attitude_setAttitude(Attitude* const me, double roll, double pitch, double yaw);
double Attitude_getRoll(const Attitude* const me);
double Attitude_getPitch(const Attitude* const me);
double Attitude_getYaw(const Attitude* const me);

#endif /* ATTITUDE_H */
