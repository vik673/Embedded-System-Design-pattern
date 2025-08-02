#include "QueuingExample.h"
#include "GasDataQueue.h"
#include "SensorThread.h"
#include "GasProcessingThread.h"
#include "GasDisplay.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#define SLEEP_MS(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP_MS(ms) usleep((ms) * 1000)
#endif

int main() {
    /* Initialize random seed */
    srand((unsigned int)time(NULL));
    
    printf("=== Queuing Pattern Example ===\n");
    printf("Demonstrating asynchronous communication between sensor and processing threads\n\n");
    
    /* Create the shared queue */
    GasDataQueue* queue = GasDataQueue_Create();
    if (!queue) {
        printf("Failed to create gas data queue\n");
        return -1;
    }
    
    /* Create sensor thread */
    SensorThread* sensorThread = SensorThread_Create();
    if (!sensorThread) {
        printf("Failed to create sensor thread\n");
        GasDataQueue_Destroy(queue);
        return -1;
    }
    SensorThread_setItsGasDataQueue(sensorThread, queue);
    
    /* Create processing thread */
    GasProcessingThread* processingThread = GasProcessingThread_Create();
    if (!processingThread) {
        printf("Failed to create processing thread\n");
        SensorThread_Destroy(sensorThread);
        GasDataQueue_Destroy(queue);
        return -1;
    }
    GasProcessingThread_setItsGasDataQueue(processingThread, queue);
    
    /* Create and set up display */
    GasDisplay* display = GasDisplay_Create();
    if (!display) {
        printf("Failed to create gas display\n");
        GasProcessingThread_Destroy(processingThread);
        SensorThread_Destroy(sensorThread);
        GasDataQueue_Destroy(queue);
        return -1;
    }
    GasController_setItsGasDisplay(&(processingThread->itsGasController), display);
    
    printf("Starting simulation...\n");
    printf("SensorThread period: 500ms\n");
    printf("GasProcessingThread period: 1000ms\n");
    printf("Queue size: %d\n\n", GAS_QUEUE_SIZE);
    
    /* Simulate the threads running for 4 seconds */
    int sensorCounter = 0;
    int processingCounter = 0;
    const int SENSOR_PERIOD_MS = 500;
    const int PROCESSING_PERIOD_MS = 1000;
    const int SIMULATION_TIME_MS = 4000;
    const int TICK_MS = 100; /* 100ms tick for simulation */
    
    for (int elapsed = 0; elapsed < SIMULATION_TIME_MS; elapsed += TICK_MS) {
        /* Check if it's time for sensor thread to run */
        if ((elapsed % SENSOR_PERIOD_MS) == 0) {
            printf("\n[%d ms] Sensor Thread Execution #%d\n", elapsed, ++sensorCounter);
            SensorThread_updateData(sensorThread);
        }
        
        /* Check if it's time for processing thread to run */
        if ((elapsed % PROCESSING_PERIOD_MS) == 0) {
            printf("\n[%d ms] Processing Thread Execution #%d\n", elapsed, ++processingCounter);
            GasProcessingThread_processData(processingThread);
        }
        
        /* Sleep for one tick */
        SLEEP_MS(TICK_MS);
    }
    
    printf("\n=== Simulation Complete ===\n");
    printf("Total sensor executions: %d\n", sensorCounter);
    printf("Total processing executions: %d\n", processingCounter);
    
    /* Cleanup */
    GasDisplay_Destroy(display);
    GasProcessingThread_Destroy(processingThread);
    SensorThread_Destroy(sensorThread);
    GasDataQueue_Destroy(queue);
    
    printf("\nQueuing Pattern demonstration completed successfully!\n");
    return 0;
}
