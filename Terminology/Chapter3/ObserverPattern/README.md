# Observer Pattern Implementation

This directory contains a complete implementation of the Observer Pattern as described in the embedded systems design pattern documentation.

## Files

- **ObserverPattern.h** - Header file containing all struct definitions and function prototypes
- **ObserverPattern.c** - Implementation file with all the pattern logic
- **demo.c** - Demonstration program showing the pattern in action
- **Makefile** - Build configuration for easy compilation

## Pattern Components

### AbstractSubject (GasSensor)
The data server that maintains a list of subscribers and notifies them when new data arrives.

**Key Functions:**
- `GasSensor_subscribe()` - Add a client to the notification list
- `GasSensor_unsubscribe()` - Remove a client from the notification list  
- `GasSensor_notify()` - Notify all subscribed clients
- `GasSensor_newData()` - Update sensor data and trigger notifications
- `GasSensor_dumpList()` - Display current subscriber list

### AbstractClient Interface
Defines the accept function that clients must implement to receive notifications.

### ConcreteClients
Three example client implementations:

1. **DisplayMonitor** - Shows gas readings on a display
2. **AlarmSystem** - Triggers alarms when readings exceed threshold
3. **DataLogger** - Logs readings to a file

### NotificationHandle
Contains function pointer and instance data for each subscriber, enabling the callback mechanism.

## Key Features

- **Dynamic Subscription**: Clients can subscribe/unsubscribe at runtime
- **Type Safety**: Function pointers ensure correct callback signatures
- **Memory Management**: Proper allocation and cleanup of resources
- **Error Handling**: Return codes indicate success/failure of operations
- **Multiple Clients**: Supports up to 10 concurrent subscribers (configurable)

## Building and Running

```bash
# Compile the demo
make

# Run the demonstration
./observer_demo

# Clean build artifacts
make clean
```

## Design Notes

This implementation follows the embedded C pattern described in the documentation:

- Uses struct-based "classes" with function pointers
- Implements the "me" pointer pattern for instance data
- Uses arrays for subscriber management (suitable for embedded systems)
- Includes proper error handling and resource management
- Demonstrates the notification mechanism exactly as described in the text

## Example Output

The demo shows:
1. Client subscription process
2. Gas sensor readings triggering notifications
3. Different client responses (display, alarm, logging)
4. Dynamic unsubscription
5. Error handling for edge cases

This implementation demonstrates how the Observer Pattern enables loose coupling between data producers (sensors) and consumers (displays, alarms, loggers) in embedded systems.
