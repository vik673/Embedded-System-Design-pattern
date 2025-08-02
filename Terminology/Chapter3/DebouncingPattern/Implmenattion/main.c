#include <stdio.h>
#include <stdlib.h>
#include "Button.h"
#include "ButtonDriver.h"
#include "MicrowaveEmitter.h"
#include "Timer.h"

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP_MS(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define SLEEP_MS(ms) usleep((ms) * 1000)
#endif

void simulateButtonBouncing(Button* button) {
    printf("\n=== Simulating Button Bouncing ===\n");
    
    /* Simulate multiple rapid state changes (bouncing) */
    printf("Simulating bouncing during button press...\n");
    Button_setState(button, 1);  /* First contact */
    SLEEP_MS(1);
    Button_setState(button, 0);  /* Bounce */
    SLEEP_MS(2);
    Button_setState(button, 1);  /* Contact again */
    SLEEP_MS(1);
    Button_setState(button, 0);  /* Bounce */
    SLEEP_MS(3);
    Button_setState(button, 1);  /* Final stable contact */
    
    /* Trigger the event after bouncing settles */
    Button_pressButton(button);
    
    /* Wait a bit */
    SLEEP_MS(100);
    
    /* Simulate bouncing during button release */
    printf("\nSimulating bouncing during button release...\n");
    Button_setState(button, 0);  /* First release */
    SLEEP_MS(2);
    Button_setState(button, 1);  /* Bounce back */
    SLEEP_MS(1);
    Button_setState(button, 0);  /* Release again */
    SLEEP_MS(3);
    Button_setState(button, 1);  /* Bounce */
    SLEEP_MS(1);
    Button_setState(button, 0);  /* Final stable release */
    
    /* Trigger the event after bouncing settles */
    Button_releaseButton(button);
}

int main(void) {
    printf("=== Debouncing Pattern Demo ===\n");
    printf("This demo shows how the debouncing pattern prevents\n");
    printf("false triggering due to mechanical switch bouncing.\n\n");
    
    /* Create all components */
    Button* button = Button_Create();
    ButtonDriver* buttonDriver = ButtonDriver_Create();
    MicrowaveEmitter* emitter = MicrowaveEmitter_Create();
    Timer* timer = Timer_Create();
    
    if (!button || !buttonDriver || !emitter || !timer) {
        printf("Error: Failed to create components\n");
        return 1;
    }
    
    /* Set up timer resolution (simulate embedded system constraints) */
    Timer_setResolution(timer, 5);  /* 5ms resolution */
    
    /* Wire up the components */
    printf("Setting up component relationships...\n");
    ButtonDriver_setItsButton(buttonDriver, button);
    ButtonDriver_setItsMicrowaveEmitter(buttonDriver, emitter);
    ButtonDriver_setItsTimer(buttonDriver, timer);
    
    /* Set microwave power level */
    MicrowaveEmitter_setPowerLevel(emitter, 75);
    
    printf("\nInitial state:\n");
    printf("- Button state: %s\n", Button_getState(button) ? "PRESSED" : "RELEASED");
    printf("- Microwave: %s\n", MicrowaveEmitter_isEmittingMicrowaves(emitter) ? "ON" : "OFF");
    
    /* Demo 1: Normal button press/release cycle */
    printf("\n=== Demo 1: Normal Button Operation ===\n");
    printf("Press button to turn on microwave...\n");
    Button_pressButton(button);
    
    SLEEP_MS(200);  /* Wait a bit */
    
    printf("\nRelease button...\n");
    Button_releaseButton(button);
    
    SLEEP_MS(200);  /* Wait a bit */
    
    printf("\nPress button again to turn off microwave...\n");
    Button_pressButton(button);
    
    SLEEP_MS(200);  /* Wait a bit */
    
    printf("\nRelease button...\n");
    Button_releaseButton(button);
    
    /* Demo 2: Button bouncing simulation */
    printf("\n=== Demo 2: Button Bouncing Simulation ===\n");
    printf("This simulates what happens with mechanical switch bouncing.\n");
    printf("The debouncing pattern should filter out the false events.\n");
    
    simulateButtonBouncing(button);
    
    SLEEP_MS(200);  /* Wait for debounce */
    
    printf("\n=== Demo 3: Rapid Button Presses (Bounce Test) ===\n");
    printf("Testing rapid button presses that might be caused by bouncing...\n");
    
    for (int i = 0; i < 3; i++) {
        printf("\nRapid press/release cycle %d:\n", i + 1);
        Button_pressButton(button);
        SLEEP_MS(10);  /* Very short time - less than debounce period */
        Button_releaseButton(button);
        SLEEP_MS(10);
    }
    
    /* Wait for final debounce */
    SLEEP_MS(100);
    
    printf("\n=== Final State ===\n");
    printf("- Button state: %s\n", Button_getState(button) ? "PRESSED" : "RELEASED");
    printf("- Microwave: %s\n", MicrowaveEmitter_isEmittingMicrowaves(emitter) ? "ON" : "OFF");
    
    /* Cleanup */
    printf("\nCleaning up...\n");
    Button_Destroy(button);
    ButtonDriver_Destroy(buttonDriver);
    MicrowaveEmitter_Destroy(emitter);
    Timer_Destroy(timer);
    
    printf("\nDebouncing pattern demo completed successfully!\n");
    printf("\nKey Benefits Demonstrated:\n");
    printf("1. False events from bouncing are filtered out\n");
    printf("2. Only stable state changes trigger actions\n");
    printf("3. Configurable debounce timing\n");
    printf("4. Clean separation of concerns between components\n");
    
    return 0;
}
