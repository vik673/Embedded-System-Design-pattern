# Decomposed AND-State Pattern

## Overview
The Decomposed AND-State Pattern decomposes a system's global state into multiple orthogonal regions that operate concurrently. In this implementation, the context class (e.g., LightController) governs the overall state while delegating state-specific behavior to independent regions such as the ErrorStateClass and ModeStateClass. These regions are managed by a container (AndStateList) and interact with device-specific classes (e.g., Light and Klaxon) to reflect state-dependent outputs.

## Diagram Overview

### State Diagram
- Illustrates high-level states (OFF_STATE, ON_STATE, EMERGENCY_STATE) and shows orthogonal regions within the ON state.
- Events are broadcast to all regions, where transitions are guarded by conditions that may combine error and mode status.

### Class Diagram
- **Key Classes**:
  - **LightController** (context): Manages high-level state transitions and coordinates the AND states.
  - **ErrorStateClass** and **ModeStateClass** (AND-state classes): Implement independent behaviors for error handling and mode control.
  - **AndStateList** (container): Manages the collection of state regions.
  - **Light** and **Klaxon** (devices): Represent hardware interfaces controlled by the state logic.
- **Explanation**:  
  The class diagram (see *ClassDiagram.puml*) shows how LightController aggregates and interacts with its sub-states. The AND-state classes encapsulate behavior specific to their domain, ensuring loose coupling and independent evolution. The container design (AndStateList) allows dynamic management of the state regions.

### Sequence Diagram
- **Example Flow**:
  - System initialization: LightController creates state regions.
  - Event handling: On an ON event, LightController broadcasts the event to both ErrorStateClass and ModeStateClass.  
  - State transitions: The context aggregates responses from each state and then delegates actions to device classes (e.g., turning the light on or activating the klaxon in emergencies).
- **Explanation**:  
  The sequence diagram (see *SequenceDiagram.puml*) demonstrates how events are received and processed concurrently by different state regions. It highlights the initialization of regions by the context, followed by event delegation and coordinated action across the devices.

## Usage Guidelines
1. **For Understanding**:  
   - Start with the State Diagram to get a conceptual overview.  
   - Refer to the Class Diagram for architecture details.  
   - Review the Sequence Diagram to see step-by-step event handling.
2. **For Implementation**:  
   - Adapt the class structure to your domain, ensuring that each orthogonal region is independently managed.  
   - Implement event broadcasting in your context class to coordinate region state transitions.

## Integration with Code
- The diagrams correspond to the following implementation files:
  - `LightController.h/.c` – Context
  - `ErrorStateClass.h/.c` – Error region behavior
  - `ModeStateClass.h/.c` – Mode region behavior
  - `AndStateList.h/.c` – Container for state regions
  - `Light.h/.c`, `Klaxon.h/.c` – Hardware device interfaces

## Commands

### Compilation
```bash
gcc -o DecomposedAndStatePattern.exe LightController.c ErrorStateClass.c ModeStateClass.c AndStateList.c Light.c Klaxon.c
```

### Execution
```bash
./DecomposedAndStatePattern.exe
```