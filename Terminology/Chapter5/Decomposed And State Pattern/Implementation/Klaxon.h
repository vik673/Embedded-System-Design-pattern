#ifndef Klaxon_H
#define Klaxon_H

typedef struct Klaxon Klaxon;
struct Klaxon {
    int isAlarming;
};

void Klaxon_Init(Klaxon* const me);
void Klaxon_Cleanup(Klaxon* const me);
void Klaxon_alarmOn(Klaxon* const me);
void Klaxon_alarmOff(Klaxon* const me);
int Klaxon_isAlarming(const Klaxon* const me);
Klaxon * Klaxon_Create(void);
void Klaxon_Destroy(Klaxon* const me);

#endif
