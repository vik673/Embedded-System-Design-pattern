#ifndef KINEMATIC_MODEL_CLIENT_H
#define KINEMATIC_MODEL_CLIENT_H

#include "PositionSensor.h"
#include "VelocitySensor.h"
#include "AttitudeSensor.h"

typedef struct KinematicModelClient KinematicModelClient;

struct KinematicModelClient {
    PositionSensor* positionSensor;
    VelocitySensor* velocitySensor;
    AttitudeSensor* attitudeSensor;
};

void KinematicModelClient_Init(KinematicModelClient* const me);
void KinematicModelClient_Cleanup(KinematicModelClient* const me);

/* Operations */
int KinematicModelClient_collectCoherentData(KinematicModelClient* const me);
void KinematicModelClient_processData(KinematicModelClient* const me);

/* Setters for sensor references */
void KinematicModelClient_setPositionSensor(KinematicModelClient* const me, PositionSensor* sensor);
void KinematicModelClient_setVelocitySensor(KinematicModelClient* const me, VelocitySensor* sensor);
void KinematicModelClient_setAttitudeSensor(KinematicModelClient* const me, AttitudeSensor* sensor);

KinematicModelClient* KinematicModelClient_Create(void);
void KinematicModelClient_Destroy(KinematicModelClient* const me);

#endif /* KINEMATIC_MODEL_CLIENT_H */
