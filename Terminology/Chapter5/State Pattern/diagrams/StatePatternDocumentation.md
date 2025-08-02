# State Pattern Implementation

## Overview
This implementation demonstrates the **State Pattern** using a number tokenizer that can parse decimal numbers. The State Pattern allows an object to alter its behavior when its internal state changes, making the object appear to change its class.

## Problem Solved
The number tokenizer needs to parse strings containing decimal numbers (e.g., "123", "45.67", "1.23 456.78") and handle different parsing states:
- Initial state (no number being processed)
- Processing whole part of number
- Processing fractional part of number

## Pattern Structure

### Key Components

1. **State (Abstract Base Class)**
   - Defines interface for concrete states
   - Declares methods for handling different events (digit, dot, whitespace, end)

2. **Context**
   - Maintains reference to current state
   - Delegates event handling to current state
   - Contains the data being processed

3. **Concrete States**
   - `NoNumberState`: Initial state, waiting for first digit
   - `ProcessingWholeState`: Processing integer part of number
   - `ProcessingFractionState`: Processing decimal part of number

### State Transitions

```
NoNumberState --[digit]--> ProcessingWholeState
ProcessingWholeState --[digit]--> ProcessingWholeState (self)
ProcessingWholeState --[dot]--> ProcessingFractionState
ProcessingWholeState --[whitespace/end]--> NoNumberState
ProcessingFractionState --[digit]--> ProcessingFractionState (self)
ProcessingFractionState --[whitespace/end]--> NoNumberState
```

## Key Features

### 1. **Polymorphic Behavior**
Each state handles events differently:
- `NoNumberState`: Only accepts digits to start parsing
- `ProcessingWholeState`: Accumulates digits, allows transition to fraction on dot
- `ProcessingFractionState`: Processes fractional digits, rejects additional dots

### 2. **Entry and Exit Actions**
- **Entry actions**: Executed when entering a state
- **Exit actions**: Executed when leaving a state
- Ensures proper state initialization and cleanup

### 3. **Event Handling**
- **processDigit()**: Handles numeric characters
- **processDot()**: Handles decimal point
- **processWhitespace()**: Handles space/tab characters
- **processEndOfString()**: Handles end of input

### 4. **Memory Management**
- Uses `std::unique_ptr` for automatic memory management
- No manual memory allocation/deallocation required

## Usage Example

```cpp
Context tokenizer;
tokenizer.processString("123.45");
// Output: Parsed Number: 123.45

tokenizer.reset();
tokenizer.processString("67 89.1");
// Output: 
// Parsed Number: 67
// Parsed Number: 89.1
```

## Advantages

1. **Encapsulation**: State-specific behavior is encapsulated in state classes
2. **Extensibility**: Easy to add new states without modifying existing code
3. **Maintainability**: Clear separation of concerns
4. **Flexibility**: States can be shared among multiple contexts

## Disadvantages

1. **Complexity**: Increases number of classes
2. **Memory**: Each state transition may involve object creation
3. **Overhead**: Polymorphic calls have slight performance cost

## UML Diagrams

### 1. Class Diagram (`StatePatternUMLClassDiagram.puml`)
Shows the static structure of the pattern with classes and their relationships.

### 2. Sequence Diagram (`StatePatternSequenceDiagram.puml`)
Illustrates the dynamic behavior when processing the string "1.3".

### 3. State Diagram (`StatePatternStateDiagram.puml`)
Shows the state transitions and triggers.

## Compilation and Execution

```bash
# Compile
g++ -std=c++14 StatePattern.cpp -o StatePattern

# Run
./StatePattern
```

## Test Cases
The implementation includes several test cases:
- Simple integers: "123"
- Decimal numbers: "45.67"
- Multiple numbers: "1.23 456.78"
- Error cases: ".5" (starts with dot), "12.34.56" (multiple dots)

## Related Patterns
- **Strategy Pattern**: Similar structure but different intent
- **State Machine**: Formal mathematical model that this pattern implements
- **Observer Pattern**: Often used to notify about state changes

## Real-World Applications
- Parsing protocols (HTTP, JSON, XML)
- Game character states (idle, running, jumping)
- UI component states (enabled, disabled, focused)
- Workflow engines
- Compiler lexical analysis
