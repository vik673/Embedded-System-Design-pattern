#include "GuardedCallExample.h"
#include "KinematicData.h"
#include "AttitudeController.h"
#include "Navigator.h"
#include "FlightDataDisplay.h"
#include <stdio.h>

int main(void) {
    printf("Guarded Call Pattern Demo\n");
    printf("========================\n\n");
    
    /* Create the shared kinematic data resource */
    KinematicData* kinematicData = KinematicData_Create();
    
    /* Create the three clients */
    AttitudeController* attitudeController = AttitudeController_Create();
    Navigator* navigator = Navigator_Create();
    FlightDataDisplay* display = FlightDataDisplay_Create();
    
    /* Connect all clients to the shared resource */
    AttitudeController_setItsKinematicData(attitudeController, kinematicData);
    Navigator_setItsKinematicData(navigator, kinematicData);
    FlightDataDisplay_setItsKinematicData(display, kinematicData);
    
    /* Set some initial values for attitude and position */
    Attitude testAttitude;
    Position testPosition;
    
    /* Initialize attitude data */
    Attitude_Init(&testAttitude);
    Attitude_setPitch(&testAttitude, 10.5);
    Attitude_setRoll(&testAttitude, -5.2);
    Attitude_setYaw(&testAttitude, 180.0);
    
    /* Initialize position data */
    Position_Init(&testPosition);
    Position_setLatitude(&testPosition, 37.7749);   /* San Francisco latitude */
    Position_setLongitude(&testPosition, -122.4194); /* San Francisco longitude */
    Position_setAltitude(&testPosition, 1000.0);    /* 1000 feet altitude */
    
    printf("Setting initial attitude data...\n");
    KinematicData_setAttitude(kinematicData, testAttitude);
    
    printf("\nSetting initial position data...\n");
    KinematicData_setPosition(kinematicData, testPosition);
    
    printf("\nDisplaying flight data (should show the values we just set):\n");
    FlightDataDisplay_showFlightData(display);
    
    /* Simulate attitude controller updating attitude */
    printf("\nAttitude controller managing attitude...\n");
    Attitude_setPitch(&(attitudeController->ownShipAttitude), 15.0);
    Attitude_setRoll(&(attitudeController->ownShipAttitude), -3.0);
    Attitude_setYaw(&(attitudeController->ownShipAttitude), 190.0);
    AttitudeController_manageAttitude(attitudeController);
    
    /* Simulate navigator updating position */
    printf("\nNavigator updating position...\n");
    Position_setLatitude(&(navigator->ownShipPosition), 40.7128);   /* New York latitude */
    Position_setLongitude(&(navigator->ownShipPosition), -74.0060); /* New York longitude */
    Position_setAltitude(&(navigator->ownShipPosition), 2000.0);    /* 2000 feet altitude */
    Navigator_updatePosition(navigator);
    
    printf("\nDisplaying updated flight data:\n");
    FlightDataDisplay_showFlightData(display);
    
    /* Demonstrate concurrent access protection */
    printf("\nDemonstrating semaphore protection:\n");
    printf("Getting attitude and position simultaneously...\n");
    Attitude currentAttitude = KinematicData_getAttitude(kinematicData);
    Position currentPosition = KinematicData_getPosition(kinematicData);
    
    printf("Retrieved attitude: roll=%f, pitch=%f, yaw=%f\n", 
           currentAttitude.roll, currentAttitude.pitch, currentAttitude.yaw);
    printf("Retrieved position: lat=%f, long=%f, alt=%f\n", 
           currentPosition.latitude, currentPosition.longitude, currentPosition.altitude);
    
    /* Clean up */
    printf("\nCleaning up resources...\n");
    AttitudeController_Destroy(attitudeController);
    Navigator_Destroy(navigator);
    FlightDataDisplay_Destroy(display);
    KinematicData_Destroy(kinematicData);
    
    printf("Guarded Call Pattern Demo completed successfully!\n");
    return 0;
}
