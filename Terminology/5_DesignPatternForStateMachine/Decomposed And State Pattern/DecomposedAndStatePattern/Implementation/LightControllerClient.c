#include "LightControllerClient.h"
#include <stdio.h>

static void cleanUpRelations(LightControllerClient* const me);

void LightControllerClient_Init(LightControllerClient* const me) {
    // Create all the objects
    me->itsLight = Light_Create();
    me->itsKlaxon = Klaxon_Create();
    me->itsMutex = Mutex_Create();
    me->itsLightController = LightController_Create();
    
    // Set up the relationships
    LightController_setItsLight(me->itsLightController, me->itsLight);
    LightController_setItsKlaxon(me->itsLightController, me->itsKlaxon);
    LightController_setItsMutex(me->itsLightController, me->itsMutex);
}

void LightControllerClient_Cleanup(LightControllerClient* const me) {
    cleanUpRelations(me);
}

void LightControllerClient_runDemo(LightControllerClient* const me) {
    printf("\n=== Decomposed AND-State Pattern Demo ===\n");
    printf("This demo shows the Light Controller with orthogonal regions:\n");
    printf("- Error Status (OK, WARNING, ERROR)\n");
    printf("- Mode Status (STARTINGUP, OPERATIONAL, SHUTTINGDOWN)\n\n");
    
    printf("1. Enabling the system...\n");
    LightController_evEnable(me->itsLightController);
    
    printf("\n2. Sending evError event...\n");
    LightController_evError(me->itsLightController);
    
    printf("\n3. Sending evRun event...\n");
    LightController_evRun(me->itsLightController);
    
    printf("\n4. Sending evAbort event (should trigger emergency if Error AND Operational)...\n");
    LightController_evAbort(me->itsLightController);
    
    printf("\n5. Resetting the system...\n");
    LightController_evDisable(me->itsLightController);
    LightController_evEnable(me->itsLightController);
    
    printf("\n6. Warning scenario...\n");
    LightController_evWarning(me->itsLightController);
    LightController_evRun(me->itsLightController);
    
    printf("\n7. OK scenario...\n");
    LightController_evOk(me->itsLightController);
    
    printf("\n8. Shutdown sequence...\n");
    LightController_evShutDown(me->itsLightController);
    
    printf("\n9. Final disable...\n");
    LightController_evDisable(me->itsLightController);
    
    printf("\n=== Demo Complete ===\n");
}

LightControllerClient * LightControllerClient_Create(void) {
    LightControllerClient* me = (LightControllerClient *)malloc(sizeof(LightControllerClient));
    if(me!=NULL)
        LightControllerClient_Init(me);
    return me;
}

void LightControllerClient_Destroy(LightControllerClient* const me) {
    if(me!=NULL)
        LightControllerClient_Cleanup(me);
    free(me);
}

static void cleanUpRelations(LightControllerClient* const me) {
    if(me->itsLightController != NULL) {
        LightController_Destroy(me->itsLightController);
        me->itsLightController = NULL;
    }
    
    if(me->itsLight != NULL) {
        Light_Destroy(me->itsLight);
        me->itsLight = NULL;
    }
    
    if(me->itsKlaxon != NULL) {
        Klaxon_Destroy(me->itsKlaxon);
        me->itsKlaxon = NULL;
    }
    
    if(me->itsMutex != NULL) {
        Mutex_Destroy(me->itsMutex);
        me->itsMutex = NULL;
    }
}
