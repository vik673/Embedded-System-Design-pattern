#ifndef MedicalDisplay_H
#define MedicalDisplay_H

typedef int deviceData;

typedef struct MedicalDisplay MedicalDisplay;
struct MedicalDisplay {
    int isActive;
    deviceData lastO2Concentration;
    deviceData lastGasFlow;
    unsigned int lastGasFlowStatus;
    deviceData lastCircuitPressure;
};

/* Constructor and Destructor */
void MedicalDisplay_Init(MedicalDisplay* const me);
void MedicalDisplay_Cleanup(MedicalDisplay* const me);
MedicalDisplay* MedicalDisplay_Create(void);
void MedicalDisplay_Destroy(MedicalDisplay* const me);

/* Display Operations */
void MedicalDisplay_showO2Concentration(MedicalDisplay* const me, deviceData concentration);
void MedicalDisplay_showGasFlow(MedicalDisplay* const me, deviceData flow);
void MedicalDisplay_showGasFlowStatus(MedicalDisplay* const me, unsigned int status);
void MedicalDisplay_showCircuitPressure(MedicalDisplay* const me, deviceData pressure);

/* Control Operations */
void MedicalDisplay_activate(MedicalDisplay* const me);
void MedicalDisplay_deactivate(MedicalDisplay* const me);
void MedicalDisplay_clear(MedicalDisplay* const me);
void MedicalDisplay_updateAll(MedicalDisplay* const me);

#endif
