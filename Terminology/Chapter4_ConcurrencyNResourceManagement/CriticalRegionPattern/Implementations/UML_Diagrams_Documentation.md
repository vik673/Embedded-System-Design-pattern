# Critical Region Pattern - UML Diagrams

This document contains the UML diagrams for the Critical Region Pattern implementation found in the embedded system design pattern code.

## Overview

The Critical Region Pattern is used to ensure that certain sections of code execute without interruption in a preemptive multitasking environment. This is achieved by disabling task switching (or interrupts) during critical operations.

## Class Diagram

### Purpose
The class diagram shows the static structure of the Critical Region Pattern implementation, including:
- All classes and their relationships
- Key attributes and methods
- Dependencies between components

### Key Components

1. **CRRobotArmManager**: The main coordinator class that implements the critical region pattern
   - Manages three key components: CRDisplay, RobotArm, and UserInput
   - Contains the critical region implementations in `motorZero()` and `moveRobotArm()`

2. **RobotArm**: Represents the shared resource that requires protected access
   - Maintains current position (x, y, z coordinates)
   - Provides movement operations that must be atomic

3. **UserInput**: Provides input coordinates for robot movement
   - Stores user-defined target coordinates
   - Thread-safe data access methods

4. **CRDisplay**: Handles output operations
   - Displays messages and results
   - Operations are performed outside critical regions

5. **OS_TaskSwitching**: Utility class providing OS abstraction
   - Static methods for enabling/disabling task switching
   - Represents the operating system interface

### Relationships
- **Composition**: CRRobotArmManager contains instances of CRDisplay, RobotArm, and UserInput
- **Dependency**: CRRobotArmManager uses OS_TaskSwitching services

## Sequence Diagrams

### 1. Main Sequence Diagram (moveRobotArm Operation)

**Purpose**: Shows the complete flow of the `moveRobotArm()` operation, demonstrating:
- How critical regions are properly implemented
- The interaction between all components
- The timing of task switching disable/enable operations
- Proper nesting avoidance (motorZero called outside main critical region)

**Key Flow**:
1. **Pre-critical operations**: Call motorZero() (which has its own critical region)
2. **Non-critical data gathering**: Get user input coordinates
3. **Main critical region**: Disable task switching → Move robot → Enable task switching
4. **Post-critical operations**: Display results

### 2. Motor Zero Sequence Diagram (motorZero Operation)

**Purpose**: Focuses specifically on the `motorZero()` operation to clearly illustrate:
- The basic critical region pattern implementation
- Proper entry and exit from critical regions
- Error handling outside the critical region
- The atomic nature of the protected operation

**Key Flow**:
1. **Enter critical region**: OS_disable_task_switching()
2. **Critical operation**: RobotArm.moveTo(0,0,0)
3. **Exit critical region**: OS_enable_task_switching()
4. **Error handling**: Display error message if needed (outside critical region)

## Critical Region Pattern Implementation Details

### Pattern Characteristics
- **Atomic Operations**: Critical sections ensure operations complete without interruption
- **Short Duration**: Critical regions are kept as short as possible to minimize impact on system responsiveness
- **Proper Cleanup**: Task switching is always re-enabled, even if errors occur
- **No Nesting**: Nested critical regions are avoided to prevent premature re-enabling of task switching

### Usage in the Code

#### motorZero() Function
```c
void CRRobotArmManager_motorZero(CRRobotArmManager* const me) {
    int success = 1;
    
    OS_disable_task_switching();    // Critical region start
    success = RobotArm_moveTo(me->itsRobotArm, 0, 0, 0);
    OS_enable_task_switching();     // Critical region end
    
    if (!success)  // Error handling outside critical region
        CRDisplay_printMsg(me->itsCRDisplay, "Cannot zero!");
}
```

#### moveRobotArm() Function
```c
void CRRobotArmManager_moveRobotArm(CRRobotArmManager* const me) {
    int x, y, z, success = 1;
    
    // Non-critical: Call motorZero (has its own critical region)
    CRRobotArmManager_motorZero(me);
    
    // Non-critical: Get user input
    x = UserInput_getX(me->itsUserInput);
    y = UserInput_getY(me->itsUserInput);
    z = UserInput_getZ(me->itsUserInput);
    
    // Critical region for main movement
    OS_disable_task_switching();
    success = RobotArm_moveTo(me->itsRobotArm, x, y, z);
    OS_enable_task_switching();
    
    // Non-critical: Display result
    CRDisplay_printInt(me->itsCRDisplay, "Result is ", success);
}
```

## Design Decisions

### Why Avoid Nested Critical Regions?
In `moveRobotArm()`, `motorZero()` is called **before** entering the main critical region. This prevents nested critical regions where the inner function (`motorZero()`) would re-enable task switching, prematurely ending the outer critical region.

### What Operations Are Protected?
- **Robot arm movements**: These must complete atomically to ensure mechanical safety
- **Coordinate updates**: Position changes must be consistent

### What Operations Are NOT Protected?
- **User input gathering**: Can be interrupted safely
- **Display operations**: Non-critical for system safety
- **Error handling**: Can be interrupted without consequences

## Files Generated
1. `ClassDiagram.puml` - Complete class structure
2. `SequenceDiagram.puml` - Full moveRobotArm operation flow
3. `MotorZeroSequenceDiagram.puml` - Focused motorZero operation flow

These PlantUML files can be rendered using any PlantUML-compatible tool or online renderer.
