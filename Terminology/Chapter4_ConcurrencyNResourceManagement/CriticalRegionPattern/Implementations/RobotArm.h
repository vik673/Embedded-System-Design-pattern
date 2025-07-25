#ifndef RobotArm_H
#define RobotArm_H

typedef struct RobotArm RobotArm;

struct RobotArm {
    int currentX;
    int currentY;
    int currentZ;
    int isMoving;
};

/* Constructor and destructor */
void RobotArm_Init(RobotArm* const me);
void RobotArm_Cleanup(RobotArm* const me);
RobotArm* RobotArm_Create(void);
void RobotArm_Destroy(RobotArm* const me);

/* Operations */
int RobotArm_moveTo(RobotArm* const me, int x, int y, int z);
int RobotArm_getCurrentX(const RobotArm* const me);
int RobotArm_getCurrentY(const RobotArm* const me);
int RobotArm_getCurrentZ(const RobotArm* const me);
int RobotArm_isMoving(const RobotArm* const me);

#endif
