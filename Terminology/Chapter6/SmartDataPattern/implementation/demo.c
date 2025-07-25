#include <stdio.h>
#include <stdlib.h>
#include "PatientDataClass.h"
#include "AlarmManager.h"

int main() {
    printf("=== Smart Data Pattern Demo ===\n\n");
    
    // Create alarm manager
    AlarmManager* alarmMgr = AlarmManager_Create();
    
    // Create patient data
    PatientDataClass* patient = PatientDataClass_Create(alarmMgr);
    
    // Set patient name and ID
    PatientDataClass_setName(patient, "John Doe");
    
    printf("Patient Name: %s\n", PatientDataClass_getName(patient));
    
    // Test valid values
    printf("\n--- Testing Valid Values ---\n");
    PatientDataClass_setAge(patient, 35);
    PatientDataClass_setWeight(patient, 75);
    PatientDataClass_setHeartRate(patient, 72);
    PatientDataClass_setFColor(patient, RED);
    PatientDataClass_setBColor(patient, WHITE);
    
    printf("Age: %d\n", PatientDataClass_getAge(patient));
    printf("Weight: %d kg\n", PatientDataClass_getWeight(patient));
    printf("Heart Rate: %d bpm\n", PatientDataClass_getHeartRate(patient));
    printf("Foreground Color: %d\n", PatientDataClass_getFColor(patient));
    printf("Background Color: %d\n", PatientDataClass_getBColor(patient));
    
    // Test range checking
    printf("\n--- Testing Range Violations ---\n");
    
    // Test age out of range (above 130)
    printf("Setting age to 150 (should trigger alarm):\n");
    PatientDataClass_setAge(patient, 150);
    
    // Test weight out of range (above 500)
    printf("Setting weight to 600 (should trigger alarm):\n");
    PatientDataClass_setWeight(patient, 600);
    
    // Test heart rate out of range (below 0)
    printf("Setting heart rate to -10 (should trigger alarm):\n");
    PatientDataClass_setHeartRate(patient, -10);
    
    // Test color out of range
    printf("Setting foreground color to 99 (should trigger alarm):\n");
    PatientDataClass_setFColor(patient, (ColorType)99);
    
    // Check all data validity
    printf("\n--- Data Validity Check ---\n");
    ErrorCodeType result = PatientDataClass_checkAllData(patient);
    if (result == NO_ERRORS) {
        printf("All patient data is valid.\n");
    } else {
        printf("Patient data validation failed with error code: %d\n", result);
    }
    
    // Display alarm information
    printf("\n--- Alarm Manager Status ---\n");
    printf("Total alarms triggered: %d\n", AlarmManager_getAlarmCount(alarmMgr));
    printf("Current alarm: %d\n", AlarmManager_getCurrentAlarm(alarmMgr));
    printf("Last alarm message: %s\n", AlarmManager_getAlarmMessage(alarmMgr));
    
    // Clean up
    PatientDataClass_Destroy(patient);
    AlarmManager_Destroy(alarmMgr);
    
    printf("\n=== Demo Complete ===\n");
    return 0;
}
