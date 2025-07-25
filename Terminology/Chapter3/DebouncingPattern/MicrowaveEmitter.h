#ifndef MicrowaveEmitter_H
#define MicrowaveEmitter_H

typedef struct MicrowaveEmitter MicrowaveEmitter;
struct MicrowaveEmitter {
    unsigned char isEmitting;  /* 0 = off, 1 = on */
    unsigned int powerLevel;   /* Power level percentage (0-100) */
};

/* Constructor and Destructor */
void MicrowaveEmitter_Init(MicrowaveEmitter* const me);
void MicrowaveEmitter_Cleanup(MicrowaveEmitter* const me);
MicrowaveEmitter* MicrowaveEmitter_Create(void);
void MicrowaveEmitter_Destroy(MicrowaveEmitter* const me);

/* Operations */
void MicrowaveEmitter_startEmitting(MicrowaveEmitter* const me);
void MicrowaveEmitter_stopEmitting(MicrowaveEmitter* const me);
unsigned char MicrowaveEmitter_isEmittingMicrowaves(const MicrowaveEmitter* const me);
void MicrowaveEmitter_setPowerLevel(MicrowaveEmitter* const me, unsigned int power);
unsigned int MicrowaveEmitter_getPowerLevel(const MicrowaveEmitter* const me);

#endif
