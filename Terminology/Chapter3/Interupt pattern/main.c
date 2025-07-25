#include <stdio.h>
#include <stdlib.h>
#include "ButtonHandler.h"
#include "Button.h"
#include "LED.h"
#include "RobotInterruptVectorTable.h"

int main() {
    int j;
    struct Button itsButton;
    struct LED itsLED;
    
    printf("Interrupt Pattern Example\n");
    printf("========================\n\n");
    
    // Initialize Button and LED
    itsButton = Button_Create();
    itsLED = LED_Create();
    
    // Initialize interrupt vector table and old vectors
    for (j = 0; j < 10; j++) {
        ISRAddress[j] = NULL;
        oldVectors[j] = NULL;
    }
    
    // Set the LED for the ButtonHandler
    ButtonHandler_setItsLED(&itsLED);
    
    // Install interrupt vectors
    install();
    
    printf("Interrupt vectors installed:\n");
    printf("- Vector 0: Button Push Interrupt\n");
    printf("- Vector 1: Button Release Interrupt\n\n");
    
    // Simulate interrupt occurrences for demonstration
    printf("Simulating button press interrupt...\n");
    if (ISRAddress[0] != NULL) {
        ISRAddress[0]();  // Simulate button push interrupt
    }
    
    printf("\nSimulating button release interrupt...\n");
    if (ISRAddress[1] != NULL) {
        ISRAddress[1]();  // Simulate button release interrupt
    }
    
    printf("\nChecking LED state: %s\n", 
           LED_IsOn(&itsLED) ? "ON" : "OFF");
    
    // Deinstall interrupt vectors
    deinstall();
    printf("\nInterrupt vectors deinstalled.\n");
    
    // Cleanup
    Button_Destroy(&itsButton);
    LED_Destroy(&itsLED);
    
    printf("\nProgram completed successfully.\n");
    return 0;
}
