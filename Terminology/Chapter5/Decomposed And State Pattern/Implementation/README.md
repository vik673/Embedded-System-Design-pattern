# Decomposed AND-State Pattern Implementation

This project implements the **Decomposed AND-State Pattern** from embedded systems design patterns. The pattern demonstrates how to handle state machines with orthogonal regions (AND-states) that execute concurrently within a single context.

## Pattern Overview

The Decomposed AND-State Pattern addresses the implementation of state machines containing orthogonal regions (AND-states) by decomposing the problem into collaborating objects rather than creating a monolithic state machine.

### Key Concepts

- **AND-States**: Logically concurrent states that execute simultaneously
- **Orthogonal Regions**: Separate state machines within a composite state
- **Run-to-Completion Semantics**: Events are processed completely before the next event
- **Decomposition**: Breaking complex state machines into collaborating objects

## System Architecture

The Light Controller system demonstrates the pattern with:

### High-Level States
- **OFF_STATE**: System is disabled
- **ON_STATE**: System is active with two orthogonal regions
- **EMERGENCY_STATE**: Critical failure mode

### Orthogonal Regions (AND-States)
When in ON_STATE, two independent state machines run concurrently:

1. **Error Status Region**:
   - OK_STATE
   - WARNING_STATE  
   - ERROR_STATE

2. **Mode Status Region**:
   - STARTINGUP_STATE
   - OPERATIONAL_STATE
   - SHUTTINGDOWN_STATE

## Class Structure

### Core Classes

- **LightController**: Main context managing the state machine
- **ErrorStateClass**: Implements the Error Status orthogonal region
- **ModeStateClass**: Implements the Mode Status orthogonal region
- **AndStateList**: Manages arrays of orthogonal state objects
- **StateActionSet**: Function pointer table for event handlers

### Supporting Classes

- **Light**: Physical light device interface
- **Klaxon**: Alarm system interface
- **Mutex**: Thread synchronization (simplified for demo)

## Event Flow

The system responds to these events:
- `evEnable`: Turn on the system
- `evDisable`: Turn off the system
- `evOk`: Clear error conditions
- `evWarning`: Set warning state
- `evError`: Set error state
- `evRun`: Advance operational mode
- `evShutDown`: Begin shutdown sequence
- `evAbort`: Emergency abort (requires Error AND Operational states)

## Key Features

### Logical Concurrency
Both orthogonal regions receive and process the same events independently. The order of processing doesn't affect the system semantics.

### Precondition Checking
The `evAbort` event demonstrates join semantics - it only triggers if both:
- Error Status is in ERROR_STATE
- Mode Status is in OPERATIONAL_STATE

### State Entry/Exit Actions
Each region has entry and exit actions that execute when states are entered or left.

## File Structure

```
DecomposedAndStatePattern/
├── LightPkg.h              # Common types and definitions
├── LightController.h/.c    # Main state machine context
├── ErrorStateClass.h/.c   # Error status orthogonal region
├── ModeStateClass.h/.c    # Mode status orthogonal region
├── AndStateList.h/.c      # Container for orthogonal regions
├── StateActionSet.h/.c    # Function pointer collections
├── Light.h/.c             # Light device interface
├── Klaxon.h/.c           # Alarm system interface
├── Mutex.h/.c            # Synchronization primitive
├── LightControllerClient.h/.c # Demo client
├── main.c                # Main program
├── Makefile             # Build configuration
└── README.md           # This file
```

## Building and Running

### Prerequisites
- GCC compiler
- Make utility

### Build Commands

```bash
# Build the demo
make

# Clean build artifacts
make clean

# Rebuild everything
make rebuild

# Build and run
make run

# Show help
make help
```

### Windows PowerShell Commands

```powershell
# Build
mingw32-make

# Run
.\decomposed_and_state_demo.exe
```

## Demo Scenario

The demo program demonstrates:

1. **System Activation**: `evEnable` transitions from OFF to ON
2. **Error Injection**: `evError` sets error state while starting up
3. **Operational Mode**: `evRun` advances to operational state
4. **Emergency Trigger**: `evAbort` with proper preconditions
5. **Recovery Scenarios**: Various state combinations
6. **Clean Shutdown**: Proper system deactivation

## Pattern Benefits

### Advantages
- **Modularity**: Each orthogonal region is a separate class
- **Maintainability**: Clear separation of concerns
- **Extensibility**: Easy to add new orthogonal regions
- **Testability**: Individual regions can be tested separately

### Trade-offs
- **Complexity**: More objects and indirection
- **Memory**: Additional overhead for object structures
- **Performance**: Function pointer calls vs direct transitions

## State Diagrams

The implementation follows the state machine structure described in the embedded systems design pattern documentation, with:
- High-level states managed by LightController
- Orthogonal regions managed by separate state classes
- Event delegation to active orthogonal regions
- Proper entry/exit action sequencing

## Design Patterns Used

1. **Decomposed AND-State Pattern**: Main pattern implemented
2. **Multiple Event Receptor Pattern**: Each state class handles multiple events
3. **State Pattern**: Object-oriented state management
4. **Template Method**: Consistent state entry/exit handling

## Thread Safety

The implementation includes basic mutex protection for event processing, though in this demo the threading is simplified. In a real embedded system, proper synchronization would be critical.

## Embedded Systems Considerations

- **Memory Management**: All objects use explicit create/destroy
- **Real-time Constraints**: Run-to-completion semantics
- **Deterministic Behavior**: Predictable event processing
- **Resource Management**: Clean object lifecycle management

This implementation serves as a foundation for more complex embedded state machines requiring orthogonal regions and concurrent state processing.
