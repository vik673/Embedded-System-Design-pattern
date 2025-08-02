#include "CRRobotArmManager.h"
#include "CRDisplay.h"
#include "RobotArm.h"
#include "UserInput.h"
#include "OS_TaskSwitching.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("=== Critical Region Pattern Demo ===\n\n");
    
    // Create all components
    CRRobotArmManager* manager = CRRobotArmManager_Create();
    CRDisplay* display = CRDisplay_Create();
    RobotArm* robotArm = RobotArm_Create();
    UserInput* userInput = UserInput_Create();
    
    if (!manager || !display || !robotArm || !userInput) {
        printf("Error: Failed to create components\n");
        return -1;
    }
    
    // Wire up the components
    CRRobotArmManager_setItsCRDisplay(manager, display);
    CRRobotArmManager_setItsRobotArm(manager, robotArm);
    CRRobotArmManager_setItsUserInput(manager, userInput);
    
    printf("Components created and configured successfully\n\n");
    
    // Simulate user input for robot movement
    printf("--- Setting user input coordinates ---\n");
    UserInput_setCoordinates(userInput, 10, 20, 30);
    printf("User input set to: (10, 20, 30)\n\n");
    
    // Demonstrate the critical region pattern in action
    printf("--- Demonstrating Critical Region Pattern ---\n");
    printf("This will show task switching being disabled/enabled during critical operations\n\n");
    
    // Test 1: Motor zero operation (has its own critical region)
    printf("Test 1: Motor Zero Operation\n");
    CRRobotArmManager_motorZero(manager);
    printf("\n");
    
    // Test 2: Full robot arm movement (includes nested critical regions)
    printf("Test 2: Full Robot Arm Movement\n");
    printf("Note: This demonstrates nested critical regions where motorZero\n");
    printf("      is called outside the main critical region to avoid nesting issues\n");
    CRRobotArmManager_moveRobotArm(manager);
    printf("\n");
    
    // Test 3: Demonstrate what happens if we try to nest critical regions improperly
    printf("Test 3: Demonstrating Nested Critical Region Handling\n");
    printf("Manually entering critical region...\n");
    OS_disable_task_switching();
    
    printf("Attempting to call motorZero from within critical region...\n");
    printf("(In real code, this should be avoided as shown in moveRobotArm)\n");
    CRRobotArmManager_motorZero(manager);
    
    printf("Manually exiting critical region...\n");
    OS_enable_task_switching();
    printf("\n");
    
    printf("--- Demo Complete ---\n");
    printf("\nKey Points Demonstrated:\n");
    printf("1. Critical regions protect robot movement operations\n");
    printf("2. Task switching is disabled during critical operations\n");
    printf("3. Proper nesting handling prevents premature critical region exit\n");
    printf("4. Each critical operation is atomic and uninterruptible\n");
    
    // Cleanup
    CRRobotArmManager_Destroy(manager);
    CRDisplay_Destroy(display);
    RobotArm_Destroy(robotArm);
    UserInput_Destroy(userInput);
    
    return 0;
}
