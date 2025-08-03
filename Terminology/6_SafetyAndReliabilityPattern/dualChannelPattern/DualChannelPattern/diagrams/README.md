# Dual Channel Pattern - UML Diagrams

This directory contains the UML diagrams for the Dual Channel Pattern implementation, specifically demonstrating a heterogeneous redundancy system for train speed control.

## Pattern Overview

The Dual Channel Pattern provides architectural redundancy to address safety and reliability concerns by replicating channels and embedding logic that manages them. This implementation demonstrates a **Heterogeneous Redundancy Pattern** that can address both random and systematic faults.

## Diagrams

### 1. Class Diagram (`DualChannelPattern_ClassDiagram.puml`)

The class diagram shows the complete structure of the Dual Channel Pattern with the following key components:

#### Core Pattern Classes
- **AbstractDataTransform**: Base class for data transformation operations
- **AbstractTransformChecker**: Base class for validation and checking operations
- **Channel**: Container class representing a unit of redundancy
- **DualChannelPattern**: Main pattern class managing dual channels

#### Concrete Implementations
- **SpeedFilterTransform**: Filters raw speed data using low-pass filtering
- **SpeedToEngineOutputTransform**: Converts speed to engine control output using PID control
- **ReasonablenessChecker**: Validates that engine outputs are within reasonable bounds

#### Sensor Drivers (Heterogeneous)
- **OpticalWheelSpeedSensor**: Measures speed using optical wheel rotation detection
- **GPSSpeedSensor**: Calculates speed using GPS position triangulation

#### Actuator
- **EngineActuator**: Controls train engine throttle position

### 2. Sequence Diagram (`DualChannelPattern_SequenceDiagram.puml`)

The sequence diagram illustrates the complete lifecycle and operation of the dual channel system:

#### Key Scenarios Covered:

1. **System Initialization**
   - Creation and setup of both channels
   - Configuration of cross-channel references for fault detection
   - Enabling both channels for operation

2. **Normal Operation**
   - Both channels processing data simultaneously
   - Independent sensor readings and data transformation
   - Validation and actuation through reasonableness checking

3. **Single Channel Failure**
   - Automatic detection of channel fault
   - Seamless switchover to the functioning channel
   - Continued system operation with reduced redundancy

4. **Complete System Failure**
   - Both channels experiencing faults
   - Transition to fault-safe mode
   - Safe shutdown procedures

5. **System Cleanup**
   - Proper resource deallocation
   - Channel destruction and cleanup

## Implementation Features

### Heterogeneous Redundancy
- **Primary Channel**: Uses optical wheel speed sensor with frequency-based speed calculation
- **Secondary Channel**: Uses GPS sensor with position-based speed calculation
- Different hardware, algorithms, and failure modes provide protection against systematic faults

### Fault Detection and Management
- Real-time reasonableness checking of outputs
- Cross-channel validation capabilities
- Automatic channel switching on fault detection
- Fault-safe mode for complete system failures

### Data Flow Architecture
- Sensor data acquisition → Filtering → Control computation → Validation → Actuation
- Independent processing pipelines for each channel
- Shared actuator with arbitration logic

## Usage

These diagrams serve as:
1. **Design Documentation**: Complete architectural overview of the pattern
2. **Implementation Guide**: Detailed class relationships and interactions
3. **Testing Reference**: Scenarios for validation and verification
4. **Maintenance Aid**: Understanding system behavior for troubleshooting

## Pattern Variants Supported

The diagrams can be adapted for other Dual Channel Pattern variants:
- **Homogeneous Redundancy**: Use identical sensors and processing
- **Triple Modular Redundancy (TMR)**: Extend to three channels with voting
- **Sanity-Check Pattern**: Add lightweight validation channel
- **Monitor-Actuator Pattern**: Add independent monitoring channel

## Tools Required

To view and edit these diagrams:
- **PlantUML**: For rendering UML diagrams
- **VS Code with PlantUML extension**: For integrated editing and preview
- **Java Runtime**: Required by PlantUML for diagram generation

## Files in this Directory

- `DualChannelPattern_ClassDiagram.puml`: Complete class structure and relationships
- `DualChannelPattern_SequenceDiagram.puml`: Detailed interaction scenarios
- `README.md`: This documentation file

## Related Patterns

- Protected Single Channel Pattern (foundation pattern)
- Channel Pattern (simpler variant)
- One's Complement Pattern (data integrity focus)
- Smart Data Pattern (intelligent data handling)
