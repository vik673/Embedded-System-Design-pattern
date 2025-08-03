# Single Event Receptor Pattern Implementation

This directory contains a complete implementation of the Single Event Receptor Pattern for embedded systems, based on the design pattern documentation from Chapter 5.

## Pattern Overview

The Single Event Receptor Pattern provides a simple implementation of state machines that can handle both synchronous and asynchronous event delivery. It uses a single event receptor to interface between clients and the state machine.

## Implementation Structure

### Core Components

1. **Event System**
   - `TokenizerAsyncSinglePkg.h` / `TokenizerSyncSinglePkg.h` - Common definitions and event types
   - Event types: EVDIGIT, EVDOT, EVWHITESPACE, EVENDOFSTRING
   - State types: NULL_STATE, NONUMBER_STATE, GOTNUMBER_STATE
   - Substate types: NULL_SSTATE, PROCESSINGWHOLEPART_SSTATE, PROCESSINGFRACTIONALPART_SSTATE

2. **Synchronization**
   - `Mutex.h` / `Mutex.c` - Mutex implementation for thread safety
   - `OSSignal.c` - OS signal simulation for asynchronous operation

3. **Synchronous Version**
   - `TSRSyncSingleReceptor.h` / `TSRSyncSingleReceptor.c` - Synchronous state machine
   - Uses mutex to ensure run-to-completion semantics
   - Direct event processing via `eventDispatch()` function

4. **Asynchronous Version**
   - `TSRAsyncSingleReceptor.h` / `TSRAsyncSingleReceptor.c` - Asynchronous state machine
   - `TSREventQueue.h` / `TSREventQueue.c` - Event queue for buffering events
   - Uses task loop with signal waiting mechanism

5. **Demo Application**
   - `main.c` - Demonstrates both synchronous and asynchronous patterns
   - Tests number parsing functionality (e.g., "123.45", "0.789", "42.7")

## State Machine Functionality

The implemented state machine is a number tokenizer that can parse decimal numbers:

- **States**: NoNumber → GotNumber → NoNumber
- **Substates** (within GotNumber): ProcessingWholePart ↔ ProcessingFractionalPart
- **Events**: Digit, Dot, Whitespace, EndOfString

### State Transitions

1. **EVDIGIT**: Processes numerical digits, accumulating the result
2. **EVDOT**: Switches from whole part to fractional part processing
3. **EVWHITESPACE/EVENDOFSTRING**: Completes number parsing and outputs result

## Building and Running

### Prerequisites
- GCC compiler
- Make utility

### Build Commands

```bash
# Build the demo
make all

# Clean build artifacts
make clean

# Build and run demo
make run

# Show help
make help
```

### Example Output

```
Single Event Receptor Pattern Demo
===================================

=== Testing Synchronous Single Receptor ===
Parsing: 123.45
Current value of result: 1
Current value of result: 12
Current value of result: 123
Current value of result: 123.4
Current value of result: 123.45
Number: 123.45

Parsing: 0.789
Current value of result: 0
Current value of result: 0.7
Current value of result: 0.78
Current value of result: 0.789
Number: 0.789

=== Testing Asynchronous Single Receptor ===
Posting events to queue: 42.7
Signal posted
Signal posted
Signal posted
Signal posted
Signal posted
Processing events from queue:
Current value of result: 4
Current value of result: 42
Current value of result: 42.7
Number: 42.7

Demo completed successfully!
```

## Design Benefits

1. **Simplicity**: Single event receptor handles all events
2. **Flexibility**: Supports both sync and async operation modes
3. **Thread Safety**: Mutex protection for concurrent access
4. **Scalability**: Can be extended with additional states and events
5. **Reusability**: Clear separation of state logic and event handling

## Design Diagrams

The implementation includes comprehensive design documentation:

- **Class Diagrams**: See `ClassDiagram.txt` for detailed class relationships and structure
- **Sequence Diagrams**: See `SequenceDiagram.txt` for interaction flows and state transitions
- **State Machine Diagram**: See `StateMachineDiagram.txt` for state transitions and parsing logic

### Key Design Elements

- **Synchronous Pattern**: Direct event processing with mutex protection
- **Asynchronous Pattern**: Event queue with signal-based task loop
- **State Machine**: Hierarchical states (main states + substates) for number parsing
- **Memory Management**: RAII pattern with Create/Destroy pairs
- **Thread Safety**: Mutex-protected critical sections

## File Structure

```
SingleReceptorPattern/
├── ClassDiagram.txt              # ASCII class diagrams
├── SequenceDiagram.txt           # ASCII sequence diagrams
├── StateMachineDiagram.txt       # State machine transitions and logic
├── Makefile                      # Build configuration
├── README.md                     # This documentation
├── main.c                        # Demo application
├── Mutex.h/.c                    # Mutex implementation
├── OSSignal.c                    # OS signal simulation
├── TokenizerAsyncSinglePkg.h     # Async package definitions
├── TokenizerSyncSinglePkg.h      # Sync package definitions
├── TSRAsyncSingleReceptor.h/.c   # Asynchronous state machine
├── TSREventQueue.h/.c            # Event queue for async version
└── TSRSyncSingleReceptor.h/.c    # Synchronous state machine
```

## Usage Examples

### Synchronous Usage

```c
TokenizerSyncSingleReceptor* receptor = TokenizerSyncSingleReceptor_Create();
Mutex* mutex = Mutex_Create();
TokenizerSyncSingleReceptor_setItsMutex(receptor, mutex);

Event digitEvent = {EVDIGIT, {.c = '5'}};
TokenizerSyncSingleReceptor_eventDispatch(receptor, digitEvent);

TokenizerSyncSingleReceptor_Destroy(receptor);
Mutex_Destroy(mutex);
```

### Asynchronous Usage

```c
TokenizerAsyncSingleReceptor* receptor = TokenizerAsyncSingleReceptor_Create();
TSREventQueue* queue = TSREventQueue_Create();
Mutex* mutex = Mutex_Create();

TSREventQueue_setItsMutex(queue, mutex);
TokenizerAsyncSingleReceptor_setItsTSREventQueue(receptor, queue);

Event digitEvent = {EVDIGIT, {.c = '5'}};
TSREventQueue_post(queue, digitEvent);

// In separate thread: TokenizerAsyncSingleReceptor_taskLoop(receptor);
```

## Notes

- This implementation uses simplified OS signal simulation for demonstration
- In a real embedded system, replace `postSignal()` and `waitOnSignal()` with actual OS calls
- The mutex implementation is basic; use platform-specific mutex APIs in production
- Memory management follows RAII principles with Create/Destroy pairs
