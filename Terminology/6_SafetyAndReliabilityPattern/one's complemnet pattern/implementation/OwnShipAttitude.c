#include "OwnShipAttitude.h"
#include <stdlib.h>
#include <stdio.h>

// Forward declaration of private functions
static void cleanUpRelations(OwnShipAttitude* const me);

void OwnShipAttitude_Init(OwnShipAttitude* const me) {
    if (me != NULL) {
        AttitudeDataType_Init(&(me->attitude));
        AttitudeDataType_Init(&(me->invertedAttitude));
        me->itsAlarmManager = NULL;
    }
}

void OwnShipAttitude_Cleanup(OwnShipAttitude* const me) {
    if (me != NULL) {
        cleanUpRelations(me);
    }
}

void OwnShipAttitude_errorHandler(OwnShipAttitude* const me) {
    if (me != NULL && me->itsAlarmManager != NULL) {
        printf("ERROR: Memory corruption detected in attitude data!\n");
        AlarmManager_addAlarm(me->itsAlarmManager, ATTITUDE_MEMORY_FAULT);
    }
}

int OwnShipAttitude_getAttitude(OwnShipAttitude* const me, AttitudeDataType* aPtr) {
    if (me == NULL || aPtr == NULL) {
        return 0;
    }
    
    // Re-invert the stored inverted attitude
    AttitudeDataType reinvertedAttitude = OwnShipAttitude_invert(me, me->invertedAttitude);
    
    // Compare the normal attitude with the re-inverted attitude
    if (me->attitude.roll == reinvertedAttitude.roll && 
        me->attitude.yaw == reinvertedAttitude.yaw &&
        me->attitude.pitch == reinvertedAttitude.pitch) {
        
        // Data integrity check passed
        *aPtr = me->attitude;
        printf("Data integrity check: PASSED\n");
        return 1;
    }
    else {
        // Data corruption detected
        printf("Data integrity check: FAILED - Corruption detected!\n");
        printf("Normal: roll=%d, pitch=%d, yaw=%d\n", 
               me->attitude.roll, me->attitude.pitch, me->attitude.yaw);
        printf("Reinverted: roll=%d, pitch=%d, yaw=%d\n", 
               reinvertedAttitude.roll, reinvertedAttitude.pitch, reinvertedAttitude.yaw);
        
        OwnShipAttitude_errorHandler(me);
        return 0;
    }
}

AttitudeDataType OwnShipAttitude_invert(OwnShipAttitude* const me, AttitudeDataType a) {
    // Perform bit-wise inversion (one's complement)
    a.roll = ~a.roll;
    a.yaw = ~a.yaw;
    a.pitch = ~a.pitch;
    return a;
}

void OwnShipAttitude_setAttitude(OwnShipAttitude* const me, AttitudeDataType a) {
    if (me != NULL) {
        // Store the normal attitude
        me->attitude = a;
        
        // Store the bit-inverted attitude
        me->invertedAttitude = OwnShipAttitude_invert(me, a);
        
        printf("Attitude set: roll=%d, pitch=%d, yaw=%d\n", a.roll, a.pitch, a.yaw);
        printf("Inverted stored: roll=%d, pitch=%d, yaw=%d\n", 
               me->invertedAttitude.roll, me->invertedAttitude.pitch, me->invertedAttitude.yaw);
    }
}

struct AlarmManager* OwnShipAttitude_getItsAlarmManager(const OwnShipAttitude* const me) {
    if (me != NULL) {
        return (struct AlarmManager*)me->itsAlarmManager;
    }
    return NULL;
}

void OwnShipAttitude_setItsAlarmManager(OwnShipAttitude* const me, struct AlarmManager* p_AlarmManager) {
    if (me != NULL) {
        me->itsAlarmManager = p_AlarmManager;
    }
}

OwnShipAttitude* OwnShipAttitude_Create(void) {
    OwnShipAttitude* me = (OwnShipAttitude*)malloc(sizeof(OwnShipAttitude));
    if (me != NULL) {
        OwnShipAttitude_Init(me);
    }
    return me;
}

void OwnShipAttitude_Destroy(OwnShipAttitude* const me) {
    if (me != NULL) {
        OwnShipAttitude_Cleanup(me);
        free(me);
    }
}

int OwnShipAttitude_validateDataIntegrity(OwnShipAttitude* const me) {
    if (me == NULL) {
        return 0;
    }
    
    AttitudeDataType reinvertedAttitude = OwnShipAttitude_invert(me, me->invertedAttitude);
    
    return (me->attitude.roll == reinvertedAttitude.roll && 
            me->attitude.yaw == reinvertedAttitude.yaw &&
            me->attitude.pitch == reinvertedAttitude.pitch) ? 1 : 0;
}

void OwnShipAttitude_simulateCorruption(OwnShipAttitude* const me, int corruptNormal) {
    if (me == NULL) {
        return;
    }
    
    printf("Simulating memory corruption...\n");
    
    if (corruptNormal) {
        // Corrupt the normal attitude data
        me->attitude.roll += 1;  // Simulate single bit flip
        printf("Corrupted normal attitude data\n");
    } else {
        // Corrupt the inverted attitude data
        me->invertedAttitude.pitch += 1;  // Simulate single bit flip
        printf("Corrupted inverted attitude data\n");
    }
}

static void cleanUpRelations(OwnShipAttitude* const me) {
    if (me != NULL && me->itsAlarmManager != NULL) {
        me->itsAlarmManager = NULL;
    }
}
