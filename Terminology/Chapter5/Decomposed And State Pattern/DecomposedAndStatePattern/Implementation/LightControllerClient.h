#ifndef LightControllerClient_H
#define LightControllerClient_H

#include "LightController.h"
#include "Light.h"
#include "Klaxon.h"
#include "Mutex.h"

typedef struct LightControllerClient LightControllerClient;
struct LightControllerClient {
    LightController* itsLightController;
    Light* itsLight;
    Klaxon* itsKlaxon;
    Mutex* itsMutex;
};

void LightControllerClient_Init(LightControllerClient* const me);
void LightControllerClient_Cleanup(LightControllerClient* const me);
void LightControllerClient_runDemo(LightControllerClient* const me);
LightControllerClient * LightControllerClient_Create(void);
void LightControllerClient_Destroy(LightControllerClient* const me);

#endif
