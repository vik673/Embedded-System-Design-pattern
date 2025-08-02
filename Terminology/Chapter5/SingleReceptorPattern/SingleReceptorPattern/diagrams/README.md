```markdown
# Single Event Receptor Pattern

## Overview
The Single Event Receptor Pattern is a design for synchronous state machines where a single event receptor handles all events. Unlike the Multiple Event Receptor Pattern where each event has its own function, this pattern consolidates event handling into one method which interprets an event identifier (and associated data) to drive state transitions. This simplification can reduce code duplication when the set of possible events is known and limited.

## Diagram Overview

### Class Diagram
- **TokenizerSingleReceptor**:  
  - Acts as the context for the state machine.
  - Maintains state variables (stateID, subStateID, result, tensPlace).
  - Provides a single event receptor function (e.g., `handleEvent(event, data)`) that uses an internal switch-case to process various events.
  - Uses a **Mutex** for ensuring atomic state transitions.
- **Mutex**:  
  - Ensures synchronized, run-to-completion semantics of the event processing.
  
**Explanation:**  
The class diagram (see below) shows that the state machine logic is encapsulated in a single receptor method. Events are distinguished by an event code passed as a parameter. This design centralizes event interpretation and state transition, thereby simplifying the interface while still maintaining thread safety via a mutex.

### Sequence Diagram
- **Flow Description**:
  1. The client (e.g., TMRClient) sends an event (with an event code and optional data) to the single receptor.
  2. The state machine (TokenizerSingleReceptor) acquires its mutex.
  3. The receptor method processes the event using a switch-case, calls any appropriate entry/exit routines, and updates state variables accordingly.
  4. The mutex is released, and updated state is returned or output.
  
**Explanation:**  
The sequence diagram (see below) details the use of a single entry point for event processing. It ensures that the entire event processing cycle is handled atomically, thus preserving the synchronous behavior expected of the state machine while reducing the number of receptor functions.

## Usage Guidelines
- **For Understanding the Pattern:**  
  Review the class diagram for the structure and the sequence diagram for the event processing flow.
- **For Implementation:**  
  Ensure that the single receptor function correctly interprets event identifiers and manages state transitions while protecting operations with a mutex.

## Integration with Code
The diagrams correspond to the following implementation files:
- `TokenizerSingleReceptor.h/.c` – Implements the state machine with a single `handleEvent()` method.
- `Mutex.h/.c` – Provides the mutual exclusion required for safe state transitions.

## Commands

### Compile the Code
```bash
gcc -o SingleReceptorPattern.exe TokenizerSingleReceptor.c Mutex.c ...existing code...
```

### Run the Program
```bash
./SingleReceptorPattern.exe
```

...existing code...