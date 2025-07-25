# ECG Monitor System - Client-Server Architecture (Without Observer Pattern)

This implementation demonstrates a classic client-server architecture for an ECG monitoring system as described in the embedded systems design pattern documentation.

## Architecture Overview

The system consists of:

### Core Components
- **ECG_Module**: Data source that acquires ECG measurements and inserts them into the queue
- **TMDQueue**: A "leaky" circular buffer that stores TimeMarkedData without explicit removal
- **TimeMarkedData**: Data structure containing time interval and data value

### Client Components (Data Consumers)
- **HistogramDisplay**: Processes data for histogram visualization
- **QRSDetector**: Analyzes data for QRS complex detection
- **WaveformDisplay**: Handles real-time waveform display
- **ArrythmiaDetector**: Monitors for irregular heart rhythms

### Test Infrastructure
- **TestBuilder**: Manages all component instances and their relationships

## Key Features

### Leaky Queue Design
- Data is never explicitly removed from the circular buffer
- New data overwrites old data when the buffer wraps around
- Multiple clients can read the same data independently
- Each client maintains its own index position in the queue

### Client-Server Model
- ECG_Module (server) pushes data when available
- Clients (displays/detectors) pull data when needed
- Decoupled architecture allows independent client processing

## File Structure

```
src/
├── ECGPkg.h              # Main header with common definitions
├── TimeMarkedData.h/.c   # Data structure for timestamped ECG data
├── TMDQueue.h/.c         # Leaky circular buffer implementation
├── ECG_Module.h/.c       # ECG data acquisition module
├── HistogramDisplay.h/.c # Histogram visualization client
├── QRSDetector.h/.c      # QRS complex detection client
├── WaveformDisplay.h/.c  # Waveform display client
├── ArrythmiaDetector.h/.c# Arrythmia detection client
├── TestBuilder.h/.c      # Test harness and component manager
└── main.c                # Demo application
```

## Building and Running

### Prerequisites
- GCC compiler
- Make utility

### Build Commands
```bash
# Build the project
make

# Clean build files
make clean

# Build and run
make run

# Build with debug symbols
make debug
```

### Manual Compilation (if Make is not available)
```bash
gcc -Wall -Wextra -std=c99 -g src/*.c -o ecg_monitor
./ecg_monitor
```

## Program Flow

1. **Initialization**: TestBuilder creates and initializes all components
2. **Data Acquisition**: ECG_Module generates random ECG data and inserts into queue
3. **Client Processing**: Each client independently reads and processes data:
   - HistogramDisplay reads 5 data points for histogram analysis
   - QRSDetector reads 3 data points for QRS detection
   - WaveformDisplay reads 5 data points for display updates
   - ArrythmiaDetector reads 5 data points for rhythm analysis
4. **Cleanup**: TestBuilder destroys all components

## Design Characteristics

### Advantages
- Simple and straightforward implementation
- Each client controls its own data consumption rate
- Shared data access without complex synchronization

### Limitations
- Clients must actively poll for data
- No automatic notification when new data arrives
- Potential for clients to miss data if they don't read fast enough
- Tight coupling between data source and queue structure

## Output Example

```
ECG Monitor System - Client-Server Architecture Demo
=====================================================

Acquiring ECG data...
Inserting at: 0 Data #: 1 Storing data value: 12345
Inserting at: 1 Data #: 2 Storing data value: 67890
...

Histogram Display processing data:
 Histogram index: 0 TimeInterval: 1 DataValue: 12345
 Histogram index: 1 TimeInterval: 2 DataValue: 67890
...
```

This implementation serves as a baseline for comparison with the Observer Pattern implementation, demonstrating the differences in notification mechanisms and coupling between components.
