# State Pattern

## Overview
The State Pattern implements a state machine by encapsulating state-specific behavior in separate state objects. The Context (e.g., a parser or tokenizer) maintains a list of these state objects and delegates incoming events to the current state. Each state object, in turn, handles events—performing entry, exit, and transition actions—and updates the Context's current state accordingly.

## Diagram Overview

### Class Diagram
This diagram (see *ClassDiagram.puml*) illustrates:
- **Context**: Holds state variables such as `result`, `tensPlace`, and a `stateList` (array of state objects). It delegates events like `evDigit`, `evDot`, `evEndOfString`, and `evWhiteSpace` to the currently active state object.
- **State Classes**: These include `NoNumberState`, `GN_ProcessingWholeState`, and `GN_ProcessingFractionState`. Each state implements all event handlers and maintains a pointer to the Context to manipulate shared data.
- **StateActionSet**: Contains function pointers for entry, exit, and event handling to facilitate polymorphism.

### Sequence Diagram
The sequence diagram (see *SequenceDiagram.puml*) shows the following flow:
1. The client invokes an event (e.g., `evDigit('x')`) on the Context.
2. The Context locks its mutex, then delegates the event to the current state’s event handler.
3. The current state processes the event, possibly executing exit actions and performing a state transition.
4. The Context then invokes the entry actions of the new state and releases the mutex.

This flow ensures that state transitions are atomic and that entry/exit actions occur in a coordinated fashion.

## Usage Guidelines
- Use the Class Diagram as a blueprint for the structure and relationships between the Context and state classes.
- Refer to the Sequence Diagram to understand the event processing and state transition flow.
- The implementation decouples state-specific behavior into separate objects, making it easier to modify or extend the state space.

## Integration with Code
The diagrams correspond to these implementation files:
- `Context.h/.c` – The Context class managing the state machine.
- `NoNumberState.h/.c`, `GN_ProcessingWholeState.h/.c`, `GN_ProcessingFractionState.h/.c` – State classes.
- `StateActionSet.h/.c` – Provides polymorphic dispatch for event handlers.
- `Mutex.h/.c` – Supplies the mutual exclusion needed for deterministic transitions.

## Commands
```bash
gcc -o StatePattern.exe Context.c NoNumberState.c GN_ProcessingWholeState.c GN_ProcessingFractionState.c StateActionSet.c Mutex.c ...existing code...
./StatePattern.exe
```