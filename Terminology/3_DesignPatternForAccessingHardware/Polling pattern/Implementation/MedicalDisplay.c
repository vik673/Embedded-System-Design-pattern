#include "MedicalDisplay.h"
#include <stdlib.h>
#include <stdio.h>

void MedicalDisplay_Init(MedicalDisplay* const me) {
    if (me != NULL) {
        me->isActive = 1;
        me->lastO2Concentration = 0;
        me->lastGasFlow = 0;
        me->lastGasFlowStatus = 0;
        me->lastCircuitPressure = 0;
    }
}

void MedicalDisplay_Cleanup(MedicalDisplay* const me) {
    if (me != NULL) {
        me->isActive = 0;
    }
}

MedicalDisplay* MedicalDisplay_Create(void) {
    MedicalDisplay* me = (MedicalDisplay*)malloc(sizeof(MedicalDisplay));
    if (me != NULL) {
        MedicalDisplay_Init(me);
    }
    return me;
}

void MedicalDisplay_Destroy(MedicalDisplay* const me) {
    if (me != NULL) {
        MedicalDisplay_Cleanup(me);
        free(me);
    }
}

void MedicalDisplay_showO2Concentration(MedicalDisplay* const me, deviceData concentration) {
    if (me != NULL && me->isActive) {
        me->lastO2Concentration = concentration;
        printf("DISPLAY: O2 Concentration: %d%%\n", concentration);
        
        /* Add visual indicators based on concentration levels */
        if (concentration < 18 || concentration > 24) {
            printf("         [ALARM] O2 Concentration Critical!\n");
        } else if (concentration < 19 || concentration > 23) {
            printf("         [WARNING] O2 Concentration outside normal range\n");
        }
    }
}

void MedicalDisplay_showGasFlow(MedicalDisplay* const me, deviceData flow) {
    if (me != NULL && me->isActive) {
        me->lastGasFlow = flow;
        printf("DISPLAY: Gas Flow: %d cmH2O\n", flow);
        
        /* Add visual indicators based on flow levels */
        if (flow < 5 || flow > 30) {
            printf("         [ALARM] Gas Flow Critical!\n");
        } else if (flow < 8 || flow > 25) {
            printf("         [WARNING] Gas Flow outside normal range\n");
        }
    }
}

void MedicalDisplay_showGasFlowStatus(MedicalDisplay* const me, unsigned int status) {
    if (me != NULL && me->isActive) {
        me->lastGasFlowStatus = status;
        
        const char* statusText;
        switch (status) {
            case 0: statusText = "NORMAL"; break;
            case 1: statusText = "WARNING"; break;
            case 2: statusText = "ALARM"; break;
            case 3: statusText = "ERROR"; break;
            default: statusText = "UNKNOWN"; break;
        }
        
        printf("DISPLAY: Gas Flow Status: %s\n", statusText);
        
        if (status >= 2) {
            printf("         [CRITICAL] Immediate attention required!\n");
        }
    }
}

void MedicalDisplay_showCircuitPressure(MedicalDisplay* const me, deviceData pressure) {
    if (me != NULL && me->isActive) {
        me->lastCircuitPressure = pressure;
        printf("DISPLAY: Circuit Pressure: %d cmH2O\n", pressure);
        
        /* Add visual indicators based on pressure levels */
        if (pressure < 0 || pressure > 20) {
            printf("         [ALARM] Circuit Pressure Critical!\n");
        } else if (pressure > 15) {
            printf("         [WARNING] Circuit Pressure high\n");
        }
    }
}

void MedicalDisplay_activate(MedicalDisplay* const me) {
    if (me != NULL) {
        me->isActive = 1;
        printf("DISPLAY: Medical Display Activated\n");
    }
}

void MedicalDisplay_deactivate(MedicalDisplay* const me) {
    if (me != NULL) {
        me->isActive = 0;
        printf("DISPLAY: Medical Display Deactivated\n");
    }
}

void MedicalDisplay_clear(MedicalDisplay* const me) {
    if (me != NULL && me->isActive) {
        me->lastO2Concentration = 0;
        me->lastGasFlow = 0;
        me->lastGasFlowStatus = 0;
        me->lastCircuitPressure = 0;
        printf("DISPLAY: Screen Cleared\n");
    }
}

void MedicalDisplay_updateAll(MedicalDisplay* const me) {
    if (me != NULL && me->isActive) {
        printf("DISPLAY: === Current Status ===\n");
        printf("DISPLAY: O2 Concentration: %d%%\n", me->lastO2Concentration);
        printf("DISPLAY: Gas Flow: %d cmH2O\n", me->lastGasFlow);
        printf("DISPLAY: Gas Flow Status: %u\n", me->lastGasFlowStatus);
        printf("DISPLAY: Circuit Pressure: %d cmH2O\n", me->lastCircuitPressure);
        printf("DISPLAY: =====================\n");
    }
}
