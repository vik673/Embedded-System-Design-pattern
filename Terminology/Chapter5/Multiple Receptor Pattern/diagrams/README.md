# Multiple Event Receptor Pattern

## Overview
The Multiple Event Receptor Pattern (MERSM) implements synchronous state machines by assigning a unique event receptor for each event. This design simplifies state handling by isolating the processing logic of each event in its own function. Typically, the client (TMRClient) calls an event receptor (e.g., evDigit, evDot, evWhiteSpace, evEndOfString) to trigger corresponding transitions and actions. The pattern also leverages mutex locking to ensure deterministic, run-to-completion semantics for state transitions.

## Diagram Overview

### Class Diagram
- **TokenizerMultiReceptor**:  
  - Serves as the context state machine.
  - Maintains state variables (`stateID`, `subStateID`, `result`, `tensPlace`) and a mutex for synchronizing transitions.
  - Provides individual event receptor functions (e.g., `evDigit`, `evDot`, `evWhiteSpace`, `evEndOfString`) along with entry and exit actions for each state.
  
- **Mutex**:  
  - Ensures that state transitions occur without interruption.
  
*Explanation:*  
The class diagram (see *ClassDiagram.puml* below) shows that the TokenizerMultiReceptor encapsulates the state machine logic. The single mutex within the state machine ensures that each event receptor processes its event atomically. Enumerated types such as TSTATETYPE and TSUBSTATETYPE are used to represent high-level states and substates, respectively. This design promotes modularity and simplicity by isolating the handling of each event into separate methods.

### Sequence Diagram
- **Flow**:  
  1. The client (TMRClient) invokes an event receptor function on the TokenizerMultiReceptor (e.g., `evDigit` with a digit character).
  2. The TokenizerMultiReceptor acquires its mutex to enter a critical section.
  3. Based on the current state and substate, the invoked receptor executes specific actions (entry/exit functions) and updates the state variables.
  4. The mutex is released, and the updated state may be printed or further processed.
  
*Explanation:*  
The sequence diagram (see *SequenceDiagram.puml* below) details how an event is processed from reception to state update. It demonstrates how state transitions are safeguarded by the mutex, ensuring that the entire processing of an event is performed without interruption. This ensures the synchronous execution required by the pattern.

## Usage Guidelines
1. **Understanding the Pattern**:  
   - Review the state and class diagrams to understand how independent event receptors are structured within the state machine.
2. **Implementation Reference**:  
   - Use individual event receptor functions for clear, modular handling of each event.
   - Mutex locking around each event ensures that transitions are atomic.
3. **Integration**:  
   - The pattern is best applied to synchronous state machines where the client directly invokes state transition functions.

## Integration with Code
The diagrams and descriptions correspond to the following implementation files:
- `TokenizerMultiReceptor.h/.c` – Implements the state machine with separate event receptors.
- `Mutex.h/.c` – Provides synchronization to guarantee deterministic transitions.

## Commands
```bash
gcc -o MultipleReceptorPattern.exe TokenizerMultiReceptor.c Mutex.c ...existing code...
./MultipleReceptorPattern.exe
```
├── Makefile                     # Build configuration
├── ClassDiagram.puml            # UML class diagram
├── SequenceDiagram.puml         # UML sequence diagram
├── StateDiagram.puml            # State machine diagram
└── README.md                    # This documentation
```

## Event Receptors

The pattern implements four event receptors:

### 1. `evDigit(char c)`
- Processes digit characters ('0'-'9')
- Handles both whole and fractional parts
- Updates the result value accordingly

### 2. `evDot()`
- Processes decimal point character
- Transitions from whole to fractional part processing
- Ignored if already processing fractional part

### 3. `evWhiteSpace()`
- Processes whitespace characters (space, tab)
- Signals end of current number
- Outputs the parsed result

### 4. `evEndOfString()`
- Signals end of input string
- Finalizes current number if being processed
- Outputs final result

## State Actions

### Entry Actions
- **enter_GotNumber()**: Initializes tensPlace for decimal processing
- **enter_NoNumber()**: Resets result to 0.0
- **enter_ProcessingWholePart()**: Updates result with new digit
- **enter_ProcessingFractionalPart()**: Placeholder for fractional setup

### Exit Actions
- **exit_GotNumber()**: Resets sub-state to NULL_SSTATE
- **exit_NoNumber()**: No specific action needed
- **exit_ProcessingWholePart()**: No specific action needed
- **exit_ProcessingFractionalPart()**: No specific action needed

## Usage Example

```c
#include "TokenizerMultiReceptor.h"

int main() {
    // Create tokenizer
    TokenizerMultiReceptor* tokenizer = TokenizerMultiReceptor_Create();
    
    // Set up mutex for thread safety
    Mutex* mutex = Mutex_Create();
    TokenizerMultiReceptor_setItsMutex(tokenizer, mutex);
    
    // Process a number string "123.45"
    TokenizerMultiReceptor_evDigit(tokenizer, '1');
    TokenizerMultiReceptor_evDigit(tokenizer, '2');
    TokenizerMultiReceptor_evDigit(tokenizer, '3');
    TokenizerMultiReceptor_evDot(tokenizer);
    TokenizerMultiReceptor_evDigit(tokenizer, '4');
    TokenizerMultiReceptor_evDigit(tokenizer, '5');
    TokenizerMultiReceptor_evEndOfString(tokenizer);
    
    // Output: "Final Number: 123.45"
    
    // Cleanup
    Mutex_Destroy(mutex);
    TokenizerMultiReceptor_Destroy(tokenizer);
    return 0;
}
```

## Building and Running

### Prerequisites
- GCC compiler
- Make utility
- (Optional) PlantUML for diagram generation

### Build Commands

```bash
# Build the project
make

# Run the demonstration
make run

# Run in interactive mode
make interactive

# Clean build artifacts
make clean

# Debug build
make debug

# Static analysis (requires cppcheck)
make analyze
```

### Running the Demo

```bash
# Basic demo with predefined test cases
./tokenizer_demo

# Interactive mode - enter your own strings
./tokenizer_demo -i
```

## Test Cases

The implementation includes comprehensive test cases:

1. **Simple integer**: "123"
2. **Decimal number**: "123.456"
3. **Fractional starting with 0**: "0.789"
4. **Fractional starting with dot**: ".5"
5. **Multiple numbers**: "42 58"
6. **Multiple decimals**: "3.14 2.71"
7. **Trailing zero**: "100.0"
8. **Empty string**: ""

## Design Patterns Used

### 1. Multiple Event Receptor Pattern
- **Intent**: Simplify synchronous state machine implementation
- **Implementation**: Separate receptor function for each event type
- **Benefits**: Clear separation of concerns, easy maintenance

### 2. Guarded Call Pattern
- **Intent**: Ensure thread-safe state transitions
- **Implementation**: Mutex locking around event processing
- **Benefits**: Deterministic run-to-completion semantics

### 3. State Pattern
- **Intent**: Manage complex state-dependent behavior
- **Implementation**: Hierarchical states with entry/exit actions
- **Benefits**: Clear state management, easy to extend

## Performance Considerations

1. **Memory Usage**: Minimal overhead with simple state variables
2. **Thread Safety**: Mutex operations add slight overhead but ensure correctness
3. **Scalability**: O(1) event processing regardless of number of states
4. **Maintainability**: Linear complexity growth when adding new events

## Extending the Pattern

To add a new event type:

1. **Add event receptor function** in header and implementation
2. **Update state machine logic** to handle the new event
3. **Add transition actions** if needed
4. **Update client code** to call the new receptor

Example: Adding `evMinus()` for negative numbers:

```c
// In header file
void TokenizerMultiReceptor_evMinus(TokenizerMultiReceptor* const me);

// In implementation file
void TokenizerMultiReceptor_evMinus(TokenizerMultiReceptor* const me) {
    if (me == NULL) return;
    
    Mutex_lock(me->itsMutex);
    // Handle negative sign logic
    Mutex_release(me->itsMutex);
}
```

## Limitations

1. **Synchronous Only**: Best suited for synchronous state machines
2. **Event Coupling**: Client must know which receptor to call for each event
3. **Memory Overhead**: Multiple receptor functions vs. single event handler
4. **Complexity**: Can become complex with many event types

## Related Patterns

- **Single Event Receptor Pattern**: Alternative with single event handler
- **Guarded Call Pattern**: Used for thread safety
- **Critical Region Pattern**: Alternative to mutex for simpler scenarios
- **State Pattern**: General state management approach

## Conclusion

The Multiple Event Receptor Pattern provides a clean, maintainable solution for implementing synchronous finite state machines in embedded systems. Its simplicity and robustness make it an excellent choice for applications where event types are well-defined and thread safety is important.

The pattern's strength lies in its ability to break down complex event handling into simple, focused receptor functions, making the code easier to understand, test, and maintain.
