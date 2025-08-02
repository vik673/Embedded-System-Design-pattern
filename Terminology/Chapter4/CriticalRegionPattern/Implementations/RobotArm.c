#include "RobotArm.h"
#include <stdlib.h>
#include <stdio.h>

void RobotArm_Init(RobotArm* const me) {
    me->currentX = 0;
    me->currentY = 0;
    me->currentZ = 0;
    me->isMoving = 0;
}

void RobotArm_Cleanup(RobotArm* const me) {
    // Stop any ongoing movements
    me->isMoving = 0;
}

RobotArm* RobotArm_Create(void) {
    RobotArm* me = (RobotArm*)malloc(sizeof(RobotArm));
    if(me != NULL) {
        RobotArm_Init(me);
    }
    return me;
}

void RobotArm_Destroy(RobotArm* const me) {
    if(me != NULL) {
        RobotArm_Cleanup(me);
        free(me);
    }
}

int RobotArm_moveTo(RobotArm* const me, int x, int y, int z) {
    // Simulate robot arm movement
    printf("Moving robot arm from (%d,%d,%d) to (%d,%d,%d)\n", 
           me->currentX, me->currentY, me->currentZ, x, y, z);
    
    me->isMoving = 1;
    
    // Simulate movement time - in real system this would be hardware control
    // For demonstration, we'll just update the position
    me->currentX = x;
    me->currentY = y;
    me->currentZ = z;
    
    me->isMoving = 0;
    
    // Return 1 for success, 0 for failure
    // In real system, this would check for actual movement completion
    return 1;
}

int RobotArm_getCurrentX(const RobotArm* const me) {
    return me->currentX;
}

int RobotArm_getCurrentY(const RobotArm* const me) {
    return me->currentY;
}

int RobotArm_getCurrentZ(const RobotArm* const me) {
    return me->currentZ;
}

int RobotArm_isMoving(const RobotArm* const me) {
    return me->isMoving;
}
