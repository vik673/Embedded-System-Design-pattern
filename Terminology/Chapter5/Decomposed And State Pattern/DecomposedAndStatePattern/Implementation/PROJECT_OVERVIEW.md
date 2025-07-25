# Project Structure Overview

## Decomposed AND-State Pattern Implementation

This directory contains a complete implementation of the Decomposed AND-State Pattern as described in embedded systems design pattern literature.

### Quick Start

**Windows:**
```cmd
build_and_run.bat
```

**Linux/macOS:**
```bash
make run
```

### Files Overview

| File | Purpose |
|------|---------|
| `LightPkg.h` | Common type definitions and enumerations |
| `LightController.h/.c` | Main state machine context |
| `ErrorStateClass.h/.c` | Error status orthogonal region |
| `ModeStateClass.h/.c` | Mode status orthogonal region |
| `AndStateList.h/.c` | Container for orthogonal regions |
| `StateActionSet.h/.c` | Function pointer collections |
| `Light.h/.c` | Light device simulation |
| `Klaxon.h/.c` | Alarm system simulation |
| `Mutex.h/.c` | Thread synchronization |
| `LightControllerClient.h/.c` | Demo client application |
| `main.c` | Main program entry point |
| `Makefile` | Build configuration for Unix-like systems |
| `build_and_run.bat` | Build script for Windows |
| `README.md` | Detailed documentation |
| `ClassDiagram.puml` | UML class diagram |
| `StateDiagram.puml` | UML state machine diagram |

### Architecture Highlights

- **Pattern Implementation**: Complete Decomposed AND-State Pattern
- **Orthogonal Regions**: Two concurrent state machines (Error + Mode)
- **Event Delegation**: Events distributed to all active orthogonal regions
- **Precondition Logic**: Join semantics for emergency abort
- **Clean C Code**: Object-oriented design in C
- **Comprehensive Demo**: Full scenario demonstration

### Key Learning Points

1. **AND-State Decomposition**: How to break complex state machines into manageable pieces
2. **Logical Concurrency**: Run-to-completion semantics with concurrent regions
3. **Event Distribution**: How events propagate to orthogonal regions
4. **State Machine Patterns**: Multiple patterns working together
5. **Embedded Design**: Memory management and deterministic behavior

### Next Steps

- Study the code structure and relationships
- Run the demo to see the pattern in action
- Modify the state machines to add new states or events
- Experiment with different orthogonal region combinations
- Apply the pattern to your own embedded systems projects

This implementation serves as a foundation for understanding and applying the Decomposed AND-State Pattern in real embedded systems development.
