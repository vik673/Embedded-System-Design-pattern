#ifndef OwnShipAttitude_H
#define OwnShipAttitude_H

#include "AttitudeDataType.h"
#include "AlarmManager.h"

/**
 * OwnShipAttitude - Implements the One's Complement Pattern
 * 
 * This class provides memory corruption detection for critical attitude data
 * by storing data in both normal and bit-inverted forms. When data is retrieved,
 * the inverted copy is re-inverted and compared with the normal copy.
 * If they don't match, memory corruption is detected and error handling is triggered.
 */

typedef struct OwnShipAttitude OwnShipAttitude;
struct OwnShipAttitude {
    struct AttitudeDataType attitude;         // Normal attitude data
    struct AttitudeDataType invertedAttitude; // Bit-inverted attitude data
    struct AlarmManager* itsAlarmManager;     // Reference to alarm manager
};

/**
 * Initialize the OwnShipAttitude structure
 * @param me Pointer to the OwnShipAttitude to initialize
 */
void OwnShipAttitude_Init(OwnShipAttitude* const me);

/**
 * Cleanup the OwnShipAttitude structure
 * @param me Pointer to the OwnShipAttitude to cleanup
 */
void OwnShipAttitude_Cleanup(OwnShipAttitude* const me);

/**
 * Handle memory corruption errors
 * @param me Pointer to the OwnShipAttitude instance
 */
void OwnShipAttitude_errorHandler(OwnShipAttitude* const me);

/**
 * Get attitude data with corruption detection
 * @param me Pointer to the OwnShipAttitude instance
 * @param aPtr Pointer to store the retrieved attitude data
 * @return 1 if data is valid, 0 if corruption detected
 */
int OwnShipAttitude_getAttitude(OwnShipAttitude* const me, AttitudeDataType* aPtr);

/**
 * Invert attitude data (bit-wise complement)
 * @param me Pointer to the OwnShipAttitude instance
 * @param a Attitude data to invert
 * @return Inverted attitude data
 */
AttitudeDataType OwnShipAttitude_invert(OwnShipAttitude* const me, AttitudeDataType a);

/**
 * Set attitude data (stores both normal and inverted forms)
 * @param me Pointer to the OwnShipAttitude instance
 * @param a Attitude data to store
 */
void OwnShipAttitude_setAttitude(OwnShipAttitude* const me, AttitudeDataType a);

/**
 * Get the associated alarm manager
 * @param me Pointer to the OwnShipAttitude instance
 * @return Pointer to the alarm manager
 */
struct AlarmManager* OwnShipAttitude_getItsAlarmManager(const OwnShipAttitude* const me);

/**
 * Set the associated alarm manager
 * @param me Pointer to the OwnShipAttitude instance
 * @param p_AlarmManager Pointer to the alarm manager to associate
 */
void OwnShipAttitude_setItsAlarmManager(OwnShipAttitude* const me, struct AlarmManager* p_AlarmManager);

/**
 * Create a new OwnShipAttitude instance
 * @return Pointer to the created instance, NULL if creation failed
 */
OwnShipAttitude* OwnShipAttitude_Create(void);

/**
 * Destroy an OwnShipAttitude instance
 * @param me Pointer to the OwnShipAttitude to destroy
 */
void OwnShipAttitude_Destroy(OwnShipAttitude* const me);

/**
 * Validate data integrity by comparing normal and re-inverted data
 * @param me Pointer to the OwnShipAttitude instance
 * @return 1 if data is valid, 0 if corruption detected
 */
int OwnShipAttitude_validateDataIntegrity(OwnShipAttitude* const me);

/**
 * Force a memory corruption for testing purposes
 * @param me Pointer to the OwnShipAttitude instance
 * @param corruptNormal If 1, corrupt normal data; if 0, corrupt inverted data
 */
void OwnShipAttitude_simulateCorruption(OwnShipAttitude* const me, int corruptNormal);

#endif /* OwnShipAttitude_H */
