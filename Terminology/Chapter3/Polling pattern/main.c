#include <stdio.h>
#include <stdlib.h>
#include "BCPeriodicPoller.h"
#include "BCTimer.h"
#include "BreathingCircuitSensor.h"
#include "MedicalDisplay.h"

/* External function to simulate timer ticks */
void BCTimer_simulateTimerTick(void);

int main(void) {
    printf("=== Embedded System Polling Pattern Demo ===\n");
    printf("Breathing Circuit Monitoring System\n\n");

    /* Create all components */
    BCPeriodicPoller* poller = BCPeriodicPoller_Create();
    BCTimer* timer = BCTimer_Create();
    MedicalDisplay* display = MedicalDisplay_Create();
    
    /* Create three breathing circuit sensors */
    BreathingCircuitSensor* o2Sensor = BreathingCircuitSensor_Create(SENSOR_O2_CONCENTRATION);
    BreathingCircuitSensor* gasSensor = BreathingCircuitSensor_Create(SENSOR_GAS_PRESSURE);
    BreathingCircuitSensor* pressureSensor = BreathingCircuitSensor_Create(SENSOR_CIRCUIT_PRESSURE);

    if (!poller || !timer || !display || !o2Sensor || !gasSensor || !pressureSensor) {
        printf("Failed to create system components!\n");
        return -1;
    }

    printf("System components created successfully\n");

    /* Set up relationships between components */
    BCPeriodicPoller_setItsBCTimer(poller, timer);
    BCPeriodicPoller_setItsMedicalDisplay(poller, display);
    
    /* Add sensors to poller */
    BCPeriodicPoller_addItsBreathingCircuitSensor(poller, o2Sensor);
    BCPeriodicPoller_addItsBreathingCircuitSensor(poller, gasSensor);
    BCPeriodicPoller_addItsBreathingCircuitSensor(poller, pressureSensor);

    printf("System relationships established\n");

    /* Configure polling period */
    BCPeriodicPoller_setPollTime(poller, 2000); /* 2 seconds */

    /* Install interrupt handler and start polling */
    BCTimer_installInterruptHandler(timer);
    BCPeriodicPoller_startPolling(poller);

    printf("\n=== Starting Periodic Polling ===\n");
    printf("Simulating timer interrupts every 2 seconds...\n");
    printf("Press Ctrl+C to stop\n\n");

    /* Simulate periodic timer interrupts */
    int pollCount = 0;
    const int maxPolls = 10; /* Limit demo to 10 polling cycles */
    
    while (pollCount < maxPolls) {
        /* Simulate timer interrupt triggering */
        BCTimer_simulateTimerTick();
        
        /* Wait for 2 seconds to simulate the polling period */
#ifdef _WIN32
        Sleep(2000); /* Windows sleep in milliseconds */
#else
        sleep(2); /* Unix/Linux sleep in seconds */
#endif
        
        pollCount++;
        printf("Poll cycle %d completed\n\n", pollCount);
    }

    printf("=== Demo Complete ===\n");
    printf("Stopping polling system...\n");

    /* Stop polling and clean up */
    BCPeriodicPoller_stopPolling(poller);
    BCTimer_removeInterruptHandler(timer);

    printf("Final system status:\n");
    MedicalDisplay_updateAll(display);

    /* Clean up all components */
    BCPeriodicPoller_Destroy(poller);
    BCTimer_Destroy(timer);
    MedicalDisplay_Destroy(display);
    BreathingCircuitSensor_Destroy(o2Sensor);
    BreathingCircuitSensor_Destroy(gasSensor);
    BreathingCircuitSensor_Destroy(pressureSensor);

    printf("\nSystem shutdown complete.\n");
    printf("=== End of Polling Pattern Demo ===\n");

    return 0;
}
