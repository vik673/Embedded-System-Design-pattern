#include "ObserverPattern.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("=== Observer Pattern Demo ===\n\n");
    
    // Create the gas sensor (ConcreteSubject)
    GasSensor* gasSensor = GasSensor_create();
    if (gasSensor == NULL) {
        printf("Failed to create gas sensor\n");
        return -1;
    }
    
    // Create concrete clients
    DisplayMonitor* display1 = DisplayMonitor_create(1, "MainDisplay");
    DisplayMonitor* display2 = DisplayMonitor_create(2, "BackupDisplay");
    AlarmSystem* alarm = AlarmSystem_create(1, 50.0f); // Threshold: 50 ppm
    DataLogger* logger = DataLogger_create(1, "gas_sensor_log.txt");
    
    if (display1 == NULL || display2 == NULL || alarm == NULL || logger == NULL) {
        printf("Failed to create one or more clients\n");
        // Cleanup and exit
        GasSensor_destroy(gasSensor);
        DisplayMonitor_destroy(display1);
        DisplayMonitor_destroy(display2);
        AlarmSystem_destroy(alarm);
        DataLogger_destroy(logger);
        return -1;
    }
    
    printf("1. Subscribing clients to gas sensor...\n");
    
    // Subscribe clients to the gas sensor
    GasSensor_subscribe(gasSensor, DisplayMonitor_accept, display1);
    GasSensor_subscribe(gasSensor, DisplayMonitor_accept, display2);
    GasSensor_subscribe(gasSensor, AlarmSystem_accept, alarm);
    GasSensor_subscribe(gasSensor, DataLogger_accept, logger);
    
    printf("\n");
    
    // Display current subscriber list
    GasSensor_dumpList(gasSensor);
    printf("\n");
    
    printf("2. Simulating gas sensor readings...\n\n");
    
    // Simulate various gas readings
    printf("--- Reading 1: Normal level ---\n");
    GasSensor_newData(gasSensor, 25.5f, 1);
    printf("\n");
    
    printf("--- Reading 2: Slightly elevated ---\n");
    GasSensor_newData(gasSensor, 45.2f, 1);
    printf("\n");
    
    printf("--- Reading 3: Dangerous level (exceeds threshold) ---\n");
    GasSensor_newData(gasSensor, 75.8f, 1);
    printf("\n");
    
    printf("--- Reading 4: Critical level ---\n");
    GasSensor_newData(gasSensor, 95.3f, 1);
    printf("\n");
    
    printf("--- Reading 5: Back to safe level ---\n");
    GasSensor_newData(gasSensor, 30.1f, 1);
    printf("\n");
    
    printf("3. Testing unsubscribe functionality...\n");
    
    // Unsubscribe one of the displays
    printf("Unsubscribing backup display...\n");
    GasSensor_unsubscribe(gasSensor, DisplayMonitor_accept);
    printf("\n");
    
    // Display updated subscriber list
    GasSensor_dumpList(gasSensor);
    printf("\n");
    
    printf("--- Reading 6: After unsubscribing backup display ---\n");
    GasSensor_newData(gasSensor, 40.7f, 1);
    printf("\n");
    
    printf("4. Testing edge cases...\n");
    
    // Try to subscribe the same client again
    printf("Attempting to subscribe main display again (should fail)...\n");
    int result = GasSensor_subscribe(gasSensor, DisplayMonitor_accept, display1);
    if (result != 0) {
        printf("Expected failure: Cannot subscribe the same client twice (Error code: %d)\n", result);
    }
    printf("\n");
    
    // Try to unsubscribe a non-existent client
    printf("Attempting to unsubscribe non-existent client (should fail)...\n");
    result = GasSensor_unsubscribe(gasSensor, DisplayMonitor_accept);
    if (result != 0) {
        printf("Expected failure: Client not found (Error code: %d)\n", result);
    }
    printf("\n");
    
    printf("5. Final demonstration...\n");
    
    // Final reading to show remaining subscribers
    printf("--- Final reading with remaining subscribers ---\n");
    GasSensor_newData(gasSensor, 15.3f, 1);
    printf("\n");
    
    // Final subscriber list
    GasSensor_dumpList(gasSensor);
    
    printf("\n=== Demo completed successfully ===\n");
    
    // Cleanup
    GasSensor_destroy(gasSensor);
    DisplayMonitor_destroy(display1);
    DisplayMonitor_destroy(display2);
    AlarmSystem_destroy(alarm);
    DataLogger_destroy(logger);
    
    printf("All resources cleaned up.\n");
    
    return 0;
}
