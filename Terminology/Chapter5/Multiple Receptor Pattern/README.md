# Multiple Event Receptor Pattern Implementation

## Overview

This project demonstrates the implementation of the **Multiple Event Receptor Pattern (MERSM)** for embedded systems. The pattern is particularly suited for synchronous finite state machines where each event has its own dedicated receptor function, making the implementation simple and robust.

## Pattern Description

The Multiple Event Receptor Pattern addresses the need for a clean, maintainable implementation of synchronous state machines. Instead of having a single event receptor that must parse and route different event types, this pattern provides a separate receptor function for each type of event.

### Key Benefits

1. **Separation of Concerns**: Each event receptor handles only one type of event
2. **Simplicity**: Easier to understand and maintain than complex event routing logic
3. **Thread Safety**: Uses mutex to ensure deterministic run-to-completion semantics
4. **Extensibility**: Easy to add new event types without modifying existing code
5. **Robustness**: Reduced complexity leads to fewer bugs

## Architecture

### Core Components

1. **TokenizerMultiReceptor**: The main state machine implementation
2. **Event Receptors**: Dedicated functions for each event type
3. **State Management**: Hierarchical state structure with entry/exit actions
4. **Mutex**: Ensures thread-safe operations
5. **Client**: Demonstrates usage of the pattern

### State Structure

The tokenizer implements a hierarchical state machine:

```
NONUMBER_STATE
    ↓ (evDigit/evDot)
GOTNUMBER_STATE
    ├── PROCESSINGWHOLEPART_SSTATE
    └── PROCESSINGFRACTIONALPART_SSTATE
```

## File Structure

```
Implementation/
├── TokenizerTypes.h/.c          # Basic types and enumerations
├── Mutex.h/.c                   # Thread synchronization
├── TokenizerMultiReceptor.h/.c  # Main pattern implementation
├── TokenizerClient.c            # Example usage and demo
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
