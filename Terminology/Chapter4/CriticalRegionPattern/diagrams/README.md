# Critical Region Pattern

## Overview
The **Critical Region Pattern** is used in preemptive multitasking environments to ensure that a task executes a portion of its operations without interruption. This is achieved by disabling task switching (or interrupts) before the critical section begins and re-enabling it after the section ends.

## Abstract
In environments where tasks share resources or where a specific sequence of operations must execute atomically, the Critical Region Pattern is applied. It prevents interference from other tasks by disabling preemption during the critical region.

## Problem
Two main scenarios necessitate the use of critical regions:
1. **Resource Protection:** When multiple tasks may access a shared resource, concurrent access may lead to data corruption.
2. **Time-Critical Processing:** When certain operations must execute without any interruption, to maintain correct sequencing or timing.

## Pattern Structure
The structure is simple: before entering the critical section, task switching is disabled (using scheduler services or assembly directives to disable interrupts). Once the critical operations are complete, task switching is reenabled. This pattern is illustrated in our example with the `CRRobotArmManager` class.

- **CRRobotArmManager:** Manages operations like `motorZero()` and `moveRobotArm()`.  
  These functions disable task switching at the start of the critical section and reenable it at the end.
- **CRDisplay, RobotArm, and UserInput:** These components are associated with the `CRRobotArmManager` and provide necessary interfaces for user feedback, arm movement, and input collection.

## Class Diagram Explanation
The class diagram (see *ClassDiagram.puml*) shows the primary classes involved:
- **CRRobotArmManager:**  
  - Contains references to the display, robot arm, and user input.
  - Implements methods (e.g., `motorZero()` and `moveRobotArm()`) that use critical regions.
- **CRDisplay, RobotArm, UserInput:**  
  - Represent the supporting components with which the manager interacts.
  
The diagram illustrates that the `CRRobotArmManager` aggregates these components and is responsible for encapsulating critical regions around operations that must be executed without interruption.

## Sequence Diagram Explanation
The sequence diagram (see *SequenceDiagram.puml*) illustrates the runtime behavior of the critical region:
1. An application calls a function such as `CRRobotArmManager_moveRobotArm()`.
2. Within this function, `CRRobotArmManager_motorZero()` is invoked as part of the process.
3. In `motorZero()`, the task switching is disabled (using `OS_disable_task_switching()`), the critical operation (e.g., moving the robot arm to zero) is performed, and then task switching is reenabled (using `OS_enable_task_switching()`).
4. Control returns back to the main function where further noncritical operations follow.

This sequence ensures that the resource (e.g., the robot arm) is accessed safely and in the correct order without interference.

---

## Commands

### Compile the Code
```bash
gcc -o CriticalRegionPattern.exe CRRobotArmManager.c ...existing code...
```

### Execute the Code
```bash
./CriticalRegionPattern.exe
```

---

## Summary
The Critical Region Pattern is essential when tasks must execute critical operations atomically. By disabling task switching or interrupts during these operations, the system prevents race conditions and ensures data integrity.