#include "KinematicModelClient.h"
#include <stdlib.h>
#include <stdio.h>

void KinematicModelClient_Init(KinematicModelClient* const me) {
    me->positionSensor = NULL;
    me->velocitySensor = NULL;
    me->attitudeSensor = NULL;
}

void KinematicModelClient_Cleanup(KinematicModelClient* const me) {
    /* Nothing to clean up - we don't own the sensors */
}

int KinematicModelClient_collectCoherentData(KinematicModelClient* const me) {
    int result = 0;
    
    /* Lock resources in order: Position (ID=1), Velocity (ID=2), Attitude (ID=3) */
    printf("KinematicModelClient: Locking PositionSensor (ID=1)\n");
    result = PositionSensor_lockDyadic(me->positionSensor);
    if (result != 0) {
        printf("Failed to lock PositionSensor, error: %d\n", result);
        return result;
    }
    
    printf("KinematicModelClient: Locking VelocitySensor (ID=2)\n");
    result = VelocitySensor_lockDyadic(me->velocitySensor);
    if (result != 0) {
        printf("Failed to lock VelocitySensor, error: %d\n", result);
        PositionSensor_releaseDyadic(me->positionSensor);
        return result;
    }
    
    printf("KinematicModelClient: Locking AttitudeSensor (ID=3)\n");
    result = AttitudeSensor_lockDyadic(me->attitudeSensor);
    if (result != 0) {
        printf("Failed to lock AttitudeSensor, error: %d\n", result);
        VelocitySensor_releaseDyadic(me->velocitySensor);
        PositionSensor_releaseDyadic(me->positionSensor);
        return result;
    }
    
    /* All resources locked successfully - process the data */
    KinematicModelClient_processData(me);
    
    /* Release resources in reverse order */
    printf("KinematicModelClient: Releasing AttitudeSensor\n");
    AttitudeSensor_releaseDyadic(me->attitudeSensor);
    
    printf("KinematicModelClient: Releasing VelocitySensor\n");
    VelocitySensor_releaseDyadic(me->velocitySensor);
    
    printf("KinematicModelClient: Releasing PositionSensor\n");
    PositionSensor_releaseDyadic(me->positionSensor);
    
    return 0;
}

void KinematicModelClient_processData(KinematicModelClient* const me) {
    struct Position pos = PositionSensor_getPosition(me->positionSensor);
    struct Velocity vel = VelocitySensor_getVelocity(me->velocitySensor);
    struct Attitude att = AttitudeSensor_getAttitude(me->attitudeSensor);
    
    printf("KinematicModelClient: Processing coherent data:\n");
    printf("  Position: lat=%.2f, lon=%.2f, alt=%.2f\n", 
           Position_getLatitude(&pos), Position_getLongitude(&pos), Position_getAltitude(&pos));
    printf("  Velocity: x=%.2f, y=%.2f, z=%.2f\n", 
           Velocity_getX(&vel), Velocity_getY(&vel), Velocity_getZ(&vel));
    printf("  Attitude: roll=%.2f, pitch=%.2f, yaw=%.2f\n", 
           Attitude_getRoll(&att), Attitude_getPitch(&att), Attitude_getYaw(&att));
}

void KinematicModelClient_setPositionSensor(KinematicModelClient* const me, PositionSensor* sensor) {
    me->positionSensor = sensor;
}

void KinematicModelClient_setVelocitySensor(KinematicModelClient* const me, VelocitySensor* sensor) {
    me->velocitySensor = sensor;
}

void KinematicModelClient_setAttitudeSensor(KinematicModelClient* const me, AttitudeSensor* sensor) {
    me->attitudeSensor = sensor;
}

KinematicModelClient* KinematicModelClient_Create(void) {
    KinematicModelClient* me = (KinematicModelClient*)malloc(sizeof(KinematicModelClient));
    if (me != NULL) {
        KinematicModelClient_Init(me);
    }
    return me;
}

void KinematicModelClient_Destroy(KinematicModelClient* const me) {
    if (me != NULL) {
        KinematicModelClient_Cleanup(me);
        free(me);
    }
}
