# State Table Design Pattern

## Overview
The State Table Design Pattern implements a state machine by using tabular representations that map states and events to transitions. In this approach, the Context holds a table (or array) of transition rules that define the next state and associated actions for each incoming event. This design simplifies the management of state transitions—especially for systems with numerous states—by making the transition logic explicit within a state table.

## Diagram Overview

### Class Diagram
**Purpose:**  
The class diagram (see *StateTableDesignPattern_ClassDiagram.puml* below) depicts the essential elements:
- **Context:**  
  Maintains state variables (like `result`, `tensPlace`, and current state identifier) and the state table (a mapping from states and events to transition actions). It delegates incoming events to the state table logic.
- **StateTableMachine:**  
  Represents the abstract state table, encapsulating the transition rules.  
- **Mutex:**  
  Ensures run-to-completion execution of state transitions.
- **Enumerated Types:**  
  `TSTATETYPE` and `TSUBSTATETYPE` are used to represent high-level states and possible nested states, respectively.

*Explanation:*  
This design decouples the state transition decision-making from the Context. The transition table (or rules) is used by the Context to look up and execute the appropriate action based on the current state and event. This approach not only simplifies the code compared to multiple event receptors but also makes adding or modifying state transitions easier.

### Sequence Diagram
**Purpose:**  
The sequence diagram (see *StateTableDesignPattern_SequenceDiagram.puml* below) illustrates the flow when an event occurs:
1. The client calls an event handler on the Context (e.g., `evDigit`).
2. The Context locks its Mutex and looks up the transition rule in the state table.
3. The Context executes any exit actions from the current state, performs the transition action, updates its state identifier, and then calls the entry action for the new state.
4. Finally, the Mutex is released and the updated state is in effect.

*Explanation:*  
The sequence diagram shows how the Context uses a state table to classify and process events. The atomicity provided by the Mutex ensures that the entire transition sequence executes without interruption.

## Usage Guidelines
- **Understanding the Pattern:**  
  Start with the Class Diagram for the structure, then see the Sequence Diagram for the event processing flow.
- **Implementation Reference:**  
  Use a table-driven approach to map state–event pairs to transition actions and new states.
- **Integration:**  
  The pattern is ideal for synchronous state machines that require explicit and maintainable transition rules.

## Integration with Code
The diagrams correspond to these files:
- `Context.h/.c` – Holds state variables and delegates events using the state table.
- `StateTableMachine.h/.c` – Contains the transition rules.
- `Mutex.h/.c` – Provides synchronization.
- Enumerated types (`TSTATETYPE`, `TSUBSTATETYPE`) define states.

## Commands
```bash
gcc -o StateTablePattern.exe Context.c StateTableMachine.c Mutex.c ...existing code...
./StateTablePattern.exe
```
├── ClassDiagram.puml            # UML class diagram
├── StateDiagram.puml            # State machine diagram
├── SequenceDiagram.puml         # Sequence diagram
├── StateTableVisualization.puml # State table visualization
└── README.md                    # This documentation
```

## State Machine Definition

### States

1. **STATE_NONUMBER**: No number currently being processed
2. **STATE_GOTNUMBER_WHOLE**: Processing whole part of a number
3. **STATE_GOTNUMBER_FRACTIONAL**: Processing fractional part of a number

### Events

1. **EVENT_DIGIT**: Digit character ('0'-'9')
2. **EVENT_DOT**: Decimal point character ('.')
3. **EVENT_WHITESPACE**: Whitespace character (space, tab)
4. **EVENT_END_OF_STRING**: End of input signal

### Actions

1. **action_none**: No operation
2. **action_start_number**: Start processing a new number
3. **action_add_digit_whole**: Add digit to whole part
4. **action_add_digit_fractional**: Add digit to fractional part
5. **action_start_fractional**: Begin fractional part processing
6. **action_finish_number**: Complete number processing

## State Transition Table

| Current State | Event | Next State | Action |
|---------------|-------|------------|---------|
| STATE_NONUMBER | EVENT_DIGIT | STATE_GOTNUMBER_WHOLE | action_start_number |
| STATE_NONUMBER | EVENT_DOT | STATE_GOTNUMBER_FRACTIONAL | action_start_fractional |
| STATE_NONUMBER | EVENT_WHITESPACE | STATE_NONUMBER | action_none |
| STATE_NONUMBER | EVENT_END_OF_STRING | STATE_NONUMBER | action_none |
| STATE_GOTNUMBER_WHOLE | EVENT_DIGIT | STATE_GOTNUMBER_WHOLE | action_add_digit_whole |
| STATE_GOTNUMBER_WHOLE | EVENT_DOT | STATE_GOTNUMBER_FRACTIONAL | action_start_fractional |
| STATE_GOTNUMBER_WHOLE | EVENT_WHITESPACE | STATE_NONUMBER | action_finish_number |
| STATE_GOTNUMBER_WHOLE | EVENT_END_OF_STRING | STATE_NONUMBER | action_finish_number |
| STATE_GOTNUMBER_FRACTIONAL | EVENT_DIGIT | STATE_GOTNUMBER_FRACTIONAL | action_add_digit_fractional |
| STATE_GOTNUMBER_FRACTIONAL | EVENT_DOT | STATE_GOTNUMBER_FRACTIONAL | action_none |
| STATE_GOTNUMBER_FRACTIONAL | EVENT_WHITESPACE | STATE_NONUMBER | action_finish_number |
| STATE_GOTNUMBER_FRACTIONAL | EVENT_END_OF_STRING | STATE_NONUMBER | action_finish_number |

## Usage Example

```c
#include "StateTableTokenizer.h"

int main() {
    // Create tokenizer
    StateTableTokenizer* tokenizer = StateTableTokenizer_Create();
    
    // Set up mutex for thread safety
    Mutex* mutex = Mutex_Create();
    StateTableTokenizer_SetMutex(tokenizer, mutex);
    
    // Process a number string "123.45"
    StateTableTokenizer_ProcessDigit(tokenizer, '1');
    StateTableTokenizer_ProcessDigit(tokenizer, '2');
    StateTableTokenizer_ProcessDigit(tokenizer, '3');
    StateTableTokenizer_ProcessDot(tokenizer);
    StateTableTokenizer_ProcessDigit(tokenizer, '4');
    StateTableTokenizer_ProcessDigit(tokenizer, '5');
    StateTableTokenizer_ProcessEndOfString(tokenizer);
    
    // Get result
    double result = StateTableTokenizer_GetResult(tokenizer);
    printf("Parsed number: %g\n", result);
    
    // Print statistics
    StateTableTokenizer_PrintStatistics(tokenizer);
    
    // Cleanup
    Mutex_Destroy(mutex);
    StateTableTokenizer_Destroy(tokenizer);
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
./state_table_demo

# Interactive mode - enter your own strings
./state_table_demo -i
```

## Interactive Features

The demo includes several interactive features:

- **String Processing**: Enter strings to parse numbers
- **'table'**: Display the complete state transition table
- **'stats'**: Show current statistics and event counts
- **'reset'**: Reset statistics counters

## Test Cases

The implementation includes comprehensive test cases:

1. **Simple integer**: "123"
2. **Decimal number**: "123.456"
3. **Fractional starting with 0**: "0.789"
4. **Fractional starting with dot**: ".5"
5. **Multiple numbers**: "42 58"
6. **Multiple decimals**: "3.14 2.71"
7. **Number with trailing zero**: "100.0"
8. **Invalid input**: "12..34" (multiple dots)
9. **Empty string**: ""

## Implementation Details

### Core Processing Function

```c
int StateTableTokenizer_ProcessEvent(StateTableTokenizer* const me, 
                                    EventType event, 
                                    char eventData) {
    // Bounds checking
    if (event >= EVENT_MAX || me->context->currentState >= STATE_MAX) {
        return -1;
    }
    
    // Thread safety
    Mutex_lock(me->context->mutex);
    
    // Table lookup
    StateTableEntry* entry = &me->stateTable[me->context->currentState][event];
    
    // Execute action
    if (entry->actionFunc != NULL) {
        entry->actionFunc(me->context, eventData);
    }
    
    // State transition
    me->context->currentState = entry->nextState;
    
    // Release mutex
    Mutex_release(me->context->mutex);
    
    return 0;
}
```

### Action Function Example

```c
void action_add_digit_whole(TokenizerContext* context, char eventData) {
    if (context == NULL) return;
    
    context->result = context->result * 10.0 + digit(eventData);
    printf("Added digit '%c' to whole part, result = %g\n", 
           eventData, context->result);
}
```

## Performance Characteristics

1. **Time Complexity**: O(1) for state transitions
2. **Space Complexity**: O(states × events) for the state table
3. **Memory Usage**: Minimal overhead with compact data structures
4. **Thread Safety**: Mutex-protected with minimal contention
5. **Scalability**: Linear growth when adding states or events

## Comparison with Other Patterns

### State Table vs. Multiple Event Receptor Pattern

| Aspect | State Table | Multiple Event Receptor |
|--------|-------------|------------------------|
| **Lookup Time** | O(1) table lookup | O(1) direct function call |
| **Memory Usage** | Higher (table storage) | Lower (function pointers only) |
| **Maintainability** | Excellent (data-driven) | Good (separate functions) |
| **Runtime Analysis** | Excellent (table inspection) | Limited (no centralized data) |
| **Flexibility** | High (table modification) | Medium (code modification) |
| **Debugging** | Excellent (table visualization) | Good (function tracing) |

### State Table vs. Switch-Case Pattern

| Aspect | State Table | Switch-Case |
|--------|-------------|-------------|
| **Performance** | Consistent O(1) | Variable (depends on compiler) |
| **Maintainability** | High (external data) | Medium (embedded logic) |
| **Code Size** | Smaller (table-driven) | Larger (repeated patterns) |
| **Runtime Modification** | Possible (table updates) | Impossible (compiled code) |
| **Debugging** | Easy (table inspection) | Harder (scattered logic) |
| **Complexity** | Low (uniform processing) | Higher (varied implementations) |

## Extending the Pattern

### Adding a New State

1. **Add state to enumeration**:
   ```c
   typedef enum {
       STATE_NONUMBER,
       STATE_GOTNUMBER_WHOLE,
       STATE_GOTNUMBER_FRACTIONAL,
       STATE_NEGATIVE,  // New state
       STATE_MAX
   } StateType;
   ```

2. **Update state table initialization**:
   ```c
   // Add transitions for the new state
   me->stateTable[STATE_NEGATIVE][EVENT_DIGIT] = 
       {STATE_GOTNUMBER_WHOLE, ACTION_START_NEGATIVE_NUMBER, action_start_negative_number};
   ```

3. **Implement action function**:
   ```c
   void action_start_negative_number(TokenizerContext* context, char eventData) {
       context->result = -digit(eventData);
       context->tensPlace = 10.0;
   }
   ```

### Adding a New Event

1. **Add event to enumeration**:
   ```c
   typedef enum {
       EVENT_DIGIT,
       EVENT_DOT,
       EVENT_WHITESPACE,
       EVENT_END_OF_STRING,
       EVENT_MINUS,  // New event
       EVENT_MAX
   } EventType;
   ```

2. **Update all state transitions** to handle the new event.

3. **Add convenience method**:
   ```c
   int StateTableTokenizer_ProcessMinus(StateTableTokenizer* const me) {
       return StateTableTokenizer_ProcessEvent(me, EVENT_MINUS, '-');
   }
   ```

## Debugging Features

### State Table Visualization

The implementation includes a `PrintStateTable()` function that displays the complete state transition table:

```
Current State        Event              Next State               Action
============        =====              ==========               ======
STATE_NONUMBER      EVENT_DIGIT        STATE_GOTNUMBER_WHOLE    ACTION_START_NUMBER
STATE_NONUMBER      EVENT_DOT          STATE_GOTNUMBER_FRACTIONAL ACTION_START_FRACTIONAL
...
```

### Runtime Statistics

The pattern maintains detailed statistics:

- Current state and result value
- Total number of state transitions
- Count of each event type processed
- Performance metrics

### Tracing

Each state transition is logged with:
- Source state
- Event that triggered the transition
- Destination state
- Action performed

## Best Practices

1. **Initialize the table completely**: Ensure all state/event combinations have valid entries
2. **Use bounds checking**: Validate state and event indices before table access
3. **Handle invalid transitions gracefully**: Provide default actions for unexpected combinations
4. **Separate concerns**: Keep action functions focused on single responsibilities
5. **Document the state machine**: Maintain clear documentation of states, events, and transitions
6. **Use thread safety**: Protect table access in multi-threaded environments
7. **Monitor performance**: Track statistics to identify bottlenecks or unexpected behavior

## Limitations

1. **Memory overhead**: Requires storage for the complete state table
2. **Compile-time definition**: States and events must be known at compile time
3. **Table size**: Memory usage grows as O(states × events)
4. **Action complexity**: Complex actions may require additional data structures
5. **Event preprocessing**: May need event classification logic before table lookup

## Related Patterns

- **Multiple Event Receptor Pattern**: Alternative approach with dedicated event handlers
- **Single Event Receptor Pattern**: Simpler approach for basic state machines
- **Strategy Pattern**: For varying action implementations
- **Observer Pattern**: For state change notifications
- **Command Pattern**: For implementing complex actions

## Conclusion

The State Table Design Pattern provides an excellent balance of performance, maintainability, and flexibility for implementing finite state machines. Its table-driven approach makes it particularly suitable for:

- Performance-critical applications requiring O(1) state transitions
- Systems with frequently changing state logic
- Applications requiring runtime analysis and debugging
- Complex state machines with many states and events

The pattern's strength lies in its clear separation of state transition logic from business logic, making it easy to understand, modify, and debug. The comprehensive statistics and debugging features make it an excellent choice for production embedded systems where reliability and maintainability are crucial.
