#include <stdio.h>
#include <stdlib.h>
#include "OwnShipAttitude.h"
#include "AlarmManager.h"
#include "AttitudeDataType.h"

/**
 * Demonstration of the One's Complement Pattern
 * 
 * This program demonstrates:
 * 1. Normal operation with data integrity
 * 2. Memory corruption detection
 * 3. Error handling through alarm management
 */

void printSeparator(const char* title) {
    printf("\n==================== %s ====================\n", title);
}

void demonstrateNormalOperation(OwnShipAttitude* attitude) {
    printSeparator("NORMAL OPERATION");
    
    AttitudeDataType testData;
    AttitudeDataType retrievedData;
    
    // Set some test attitude data
    AttitudeDataType_Set(&testData, 15, -5, 270);
    
    printf("Setting attitude data: roll=%d, pitch=%d, yaw=%d\n", 
           testData.roll, testData.pitch, testData.yaw);
    
    OwnShipAttitude_setAttitude(attitude, testData);
    
    // Retrieve the data
    printf("\nRetrieving attitude data...\n");
    int result = OwnShipAttitude_getAttitude(attitude, &retrievedData);
    
    if (result) {
        printf("SUCCESS: Retrieved attitude data: roll=%d, pitch=%d, yaw=%d\n", 
               retrievedData.roll, retrievedData.pitch, retrievedData.yaw);
    } else {
        printf("FAILURE: Could not retrieve attitude data due to corruption\n");
    }
}

void demonstrateMemoryCorruption(OwnShipAttitude* attitude, AlarmManager* alarmManager) {
    printSeparator("MEMORY CORRUPTION DETECTION");
    
    AttitudeDataType testData;
    AttitudeDataType retrievedData;
    
    // Set initial data
    AttitudeDataType_Set(&testData, 45, 10, 180);
    printf("Setting attitude data: roll=%d, pitch=%d, yaw=%d\n", 
           testData.roll, testData.pitch, testData.yaw);
    
    OwnShipAttitude_setAttitude(attitude, testData);
    
    printf("Initial alarm count: %d\n", AlarmManager_getAlarmCount(alarmManager));
    
    // Simulate memory corruption
    printf("\nSimulating memory corruption...\n");
    OwnShipAttitude_simulateCorruption(attitude, 1); // Corrupt normal data
    
    // Try to retrieve corrupted data
    printf("\nAttempting to retrieve corrupted data...\n");
    int result = OwnShipAttitude_getAttitude(attitude, &retrievedData);
    
    if (result) {
        printf("UNEXPECTED: Data retrieved successfully despite corruption\n");
    } else {
        printf("EXPECTED: Corruption detected, data retrieval failed\n");
        printf("Alarm count after corruption: %d\n", AlarmManager_getAlarmCount(alarmManager));
        
        if (AlarmManager_isAlarmActive(alarmManager, ATTITUDE_MEMORY_FAULT)) {
            printf("ATTITUDE_MEMORY_FAULT alarm is active\n");
        }
    }
}

void demonstrateDataIntegrityValidation(OwnShipAttitude* attitude) {
    printSeparator("DATA INTEGRITY VALIDATION");
    
    AttitudeDataType testData;
    AttitudeDataType_Set(&testData, 30, -15, 90);
    
    printf("Setting test data and validating integrity...\n");
    OwnShipAttitude_setAttitude(attitude, testData);
    
    // Test integrity before corruption
    if (OwnShipAttitude_validateDataIntegrity(attitude)) {
        printf("✓ Data integrity validation: PASSED\n");
    } else {
        printf("✗ Data integrity validation: FAILED\n");
    }
    
    // Corrupt data and test again
    printf("\nCorrupting data and re-validating...\n");
    OwnShipAttitude_simulateCorruption(attitude, 0); // Corrupt inverted data
    
    if (OwnShipAttitude_validateDataIntegrity(attitude)) {
        printf("✓ Data integrity validation: PASSED (unexpected)\n");
    } else {
        printf("✗ Data integrity validation: FAILED (expected)\n");
    }
}

void demonstrateBitInversion() {
    printSeparator("BIT INVERSION DEMONSTRATION");
    
    printf("Demonstrating bit-wise inversion (One's Complement):\n\n");
    
    int originalValues[] = {15, -5, 270, 0, -1, 255};
    int numValues = sizeof(originalValues) / sizeof(originalValues[0]);
    
    for (int i = 0; i < numValues; i++) {
        int original = originalValues[i];
        int inverted = ~original;
        int reinverted = ~inverted;
        
        printf("Original: %d (0x%08X)\n", original, (unsigned int)original);
        printf("Inverted: %d (0x%08X)\n", inverted, (unsigned int)inverted);
        printf("Reinverted: %d (0x%08X)\n", reinverted, (unsigned int)reinverted);
        printf("Integrity: %s\n\n", (original == reinverted) ? "PASSED" : "FAILED");
    }
}

int main() {
    printf("One's Complement Pattern Demonstration\n");
    printf("=====================================\n");
    printf("This demonstrates memory corruption detection using bit-wise inversion\n");
    
    // Create instances
    AlarmManager* alarmManager = AlarmManager_Create();
    OwnShipAttitude* attitude = OwnShipAttitude_Create();
    
    if (alarmManager == NULL || attitude == NULL) {
        printf("Failed to create instances\n");
        return 1;
    }
    
    // Associate alarm manager with attitude monitor
    OwnShipAttitude_setItsAlarmManager(attitude, alarmManager);
    
    // Run demonstrations
    demonstrateBitInversion();
    demonstrateNormalOperation(attitude);
    demonstrateMemoryCorruption(attitude, alarmManager);
    
    // Clear alarms and test again with different corruption
    AlarmManager_clearAllAlarms(alarmManager);
    demonstrateDataIntegrityValidation(attitude);
    
    printSeparator("CLEANUP");
    printf("Cleaning up and destroying instances...\n");
    
    // Cleanup
    OwnShipAttitude_Destroy(attitude);
    AlarmManager_Destroy(alarmManager);
    
    printf("Demonstration complete.\n");
    
    return 0;
}
