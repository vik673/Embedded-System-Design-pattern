#include <stdio.h>
#include <stdlib.h>
#include "OrderedLockingExample.h"
#include "Mutex.h"
#include "ResourceList.h"
#include "PositionSensor.h"
#include "VelocitySensor.h"
#include "AttitudeSensor.h"
#include "KinematicModelClient.h"

int main(void) {
    printf("=== Ordered Locking Pattern Demonstration ===\n\n");
    
    /* Create the global resource list and its mutex */
    ResourceList* resourceList = ResourceList_Create();
    Mutex* resourceListMutex = Mutex_Create();
    ResourceList_setItsMutex(resourceList, resourceListMutex);
    
    /* Create mutexes for each sensor */
    Mutex* posMutex = Mutex_Create();
    Mutex* velMutex = Mutex_Create();
    Mutex* attMutex = Mutex_Create();
    
    /* Create sensors */
    PositionSensor* positionSensor = PositionSensor_Create();
    VelocitySensor* velocitySensor = VelocitySensor_Create();
    AttitudeSensor* attitudeSensor = AttitudeSensor_Create();
    
    /* Set up sensor relationships */
    PositionSensor_setItsMutex(positionSensor, posMutex);
    PositionSensor_setItsResourceList(positionSensor, resourceList);
    
    VelocitySensor_setItsMutex(velocitySensor, velMutex);
    VelocitySensor_setItsResourceList(velocitySensor, resourceList);
    
    AttitudeSensor_setItsMutex(attitudeSensor, attMutex);
    AttitudeSensor_setItsResourceList(attitudeSensor, resourceList);
    
    /* Initialize sensor data */
    struct Position pos;
    Position_Init(&pos);
    Position_setPosition(&pos, 37.7749, -122.4194, 1000.0);
    PositionSensor_setPosition(positionSensor, pos);
    
    struct Velocity vel;
    Velocity_Init(&vel);
    Velocity_setVelocity(&vel, 100.0, 50.0, 10.0);
    VelocitySensor_setVelocity(velocitySensor, vel);
    
    struct Attitude att;
    Attitude_Init(&att);
    Attitude_setAttitude(&att, 5.0, 2.0, 180.0);
    AttitudeSensor_setAttitude(attitudeSensor, att);
    
    /* Create client */
    KinematicModelClient* client = KinematicModelClient_Create();
    KinematicModelClient_setPositionSensor(client, positionSensor);
    KinematicModelClient_setVelocitySensor(client, velocitySensor);
    KinematicModelClient_setAttitudeSensor(client, attitudeSensor);
    
    /* Demonstrate successful ordered locking */
    printf("1. Demonstrating successful ordered locking:\n");
    int result = KinematicModelClient_collectCoherentData(client);
    if (result == 0) {
        printf("SUCCESS: All resources locked and released successfully!\n\n");
    } else {
        printf("ERROR: Failed to lock resources, error code: %d\n\n", result);
    }
    
    /* Demonstrate what happens with wrong order (simulate by trying to lock manually) */
    printf("2. Demonstrating prevention of poorly ordered access:\n");
    printf("Attempting to lock AttitudeSensor (ID=3) first...\n");
    result = AttitudeSensor_lockDyadic(attitudeSensor);
    if (result == 0) {
        printf("AttitudeSensor locked successfully\n");
        
        printf("Now attempting to lock PositionSensor (ID=1) - this should fail!\n");
        result = PositionSensor_lockDyadic(positionSensor);
        if (result == POORLY_ORDERED_ACCESS) {
            printf("SUCCESS: Poorly ordered access correctly prevented! Error code: %d\n", result);
        } else {
            printf("UNEXPECTED: PositionSensor lock result: %d\n", result);
        }
        
        printf("Releasing AttitudeSensor\n");
        AttitudeSensor_releaseDyadic(attitudeSensor);
    }
    
    printf("\n=== Pattern Demonstration Complete ===\n");
    
    /* Cleanup */
    KinematicModelClient_Destroy(client);
    PositionSensor_Destroy(positionSensor);
    VelocitySensor_Destroy(velocitySensor);
    AttitudeSensor_Destroy(attitudeSensor);
    Mutex_Destroy(posMutex);
    Mutex_Destroy(velMutex);
    Mutex_Destroy(attMutex);
    Mutex_Destroy(resourceListMutex);
    ResourceList_Destroy(resourceList);
    
    return 0;
}
