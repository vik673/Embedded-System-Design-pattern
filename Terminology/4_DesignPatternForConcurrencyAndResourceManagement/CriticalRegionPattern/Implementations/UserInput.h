#ifndef UserInput_H
#define UserInput_H

typedef struct UserInput UserInput;

struct UserInput {
    int x;
    int y;
    int z;
    int inputReady;
};

/* Constructor and destructor */
void UserInput_Init(UserInput* const me);
void UserInput_Cleanup(UserInput* const me);
UserInput* UserInput_Create(void);
void UserInput_Destroy(UserInput* const me);

/* Operations */
int UserInput_getX(const UserInput* const me);
int UserInput_getY(const UserInput* const me);
int UserInput_getZ(const UserInput* const me);
void UserInput_setCoordinates(UserInput* const me, int x, int y, int z);
int UserInput_isInputReady(const UserInput* const me);

#endif
