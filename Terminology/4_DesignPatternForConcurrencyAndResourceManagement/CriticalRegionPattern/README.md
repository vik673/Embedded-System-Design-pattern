# Critical Region Pattern Implementation

This directory contains a complete implementation of the Critical Region Pattern as described in embedded system design patterns literature.

## Overview

The Critical Region Pattern is used in preemptive multitasking environments to ensure that certain operations execute without interruption. This is achieved by disabling task switching (or interrupts) during critical sections of code.

## Pattern Structure

The implementation demonstrates two main variants of the Critical Region Pattern:

1. **Task with Critical Region**: Where a task needs uninterrupted execution for timing-critical operations
2. **Shared Resource Protection**: Where multiple tasks may access the same resource and need protection from concurrent access

## Key Components

### Core Classes

- **CRRobotArmManager**: Main coordinator that demonstrates critical region usage
- **RobotArm**: Represents the hardware being controlled
- **CRDisplay**: Output interface for system messages
- **UserInput**: Input interface for coordinates
- **OS_TaskSwitching**: OS abstraction layer for critical region control

### Critical Region Implementation

The pattern is implemented using:
```c
OS_disable_task_switching();
/* Critical region code here */
OS_enable_task_switching();
```

## Critical Operations

### Motor Zero Operation
```c
void CRRobotArmManager_motorZero(CRRobotArmManager* const me) {
    int success = 1;
    
    OS_disable_task_switching();
    /* critical region code */
    success = RobotArm_moveTo(me->itsRobotArm, 0, 0, 0);
    /* critical region ends */
    OS_enable_task_switching();
    
    if (!success)
        CRDisplay_printMsg(me->itsCRDisplay, "Cannot zero!");
}
```

### Robot Arm Movement
The `moveRobotArm` function demonstrates proper handling of nested critical regions by calling `motorZero` outside of its own critical region.

## Key Design Principles

1. **Atomic Operations**: Critical regions ensure robot movements are completed without interruption
2. **Nesting Avoidance**: Functions with critical regions should not be called from within other critical regions
3. **Short Duration**: Critical regions are kept as short as possible to minimize impact on system responsiveness
4. **Proper Cleanup**: Task switching is always re-enabled, even in error conditions

## Building and Running

### Prerequisites
- GCC compiler
- Make utility

### Build Instructions
```bash
# Build the demo
make

# Clean build artifacts
make clean

# Build and run
make run
```

### Windows PowerShell
```powershell
# Build the demo
mingw32-make

# Run the demo
./critical_region_demo.exe
```

## Expected Output

The demo will show:
1. Component initialization
2. Critical region entry/exit messages
3. Robot movement simulation
4. Demonstration of nested critical region handling

## Real-World Considerations

### RTOS Integration
In a real embedded system, replace the mock OS functions with actual RTOS calls:

**FreeRTOS Example:**
```c
void OS_disable_task_switching(void) {
    vTaskSuspendAll();
}

void OS_enable_task_switching(void) {
    xTaskResumeAll();
}
```

**Hardware Interrupt Control:**
```c
void OS_disable_task_switching(void) {
    __disable_irq();  // Disable all interrupts
}

void OS_enable_task_switching(void) {
    __enable_irq();   // Re-enable interrupts
}
```

### Performance Impact

- Critical regions should be as short as possible
- Long critical regions can cause priority inversion
- Consider using other synchronization mechanisms for longer operations

### Safety Considerations

- Always pair disable/enable calls
- Use RAII-style wrappers in C++ for automatic cleanup
- Test thoroughly under high-load conditions
- Monitor for missed deadlines in real-time systems

## Pattern Benefits

1. **Simplicity**: Easy to understand and implement
2. **Deterministic**: Guaranteed atomic execution
3. **No Priority Inversion**: All task switching is disabled
4. **Hardware Independence**: Works with any preemptive scheduler

## Pattern Limitations

1. **System Responsiveness**: Can delay other tasks
2. **Interrupt Latency**: May increase interrupt response time
3. **Deadlock Risk**: If critical regions are not properly exited
4. **Scalability**: Not suitable for systems with many concurrent operations

## Related Patterns

- **Guarded Call Pattern**: Alternative using semaphores/mutexes
- **Interrupt Pattern**: For handling asynchronous events
- **Static Priority Pattern**: Scheduling pattern often used with critical regions

## Files Description

- `CRRobotArmManager.h/.c`: Main pattern implementation
- `CRDisplay.h/.c`: Display abstraction
- `RobotArm.h/.c`: Hardware abstraction
- `UserInput.h/.c`: Input interface
- `OS_TaskSwitching.h/.c`: OS abstraction layer
- `main.c`: Demonstration program
- `Makefile`: Build configuration

## Testing

The implementation includes built-in demonstration of:
- Normal critical region operation
- Nested critical region handling
- Error conditions and recovery
- System state verification

For production use, add comprehensive unit tests and integration tests under various load conditions.
