# Dual Channel Pattern

## Overview
The Dual Channel Pattern provides redundancy by replicating channels to enhance system reliability. Depending on whether the channels are identical (Homogeneous Redundancy) or different (Heterogeneous/Diverse Redundancy), the system can protect against random faults or both random and systematic faults. A channel typically processes sensor data through several transformation steps to produce an actuator output. The Dual Channel Pattern includes additional logic (often via a transform checker) that monitors the active (current) channel and may switch to the alternative channel if a fault is detected.

## Diagram Overview

### Class Diagram
This diagram (see *DualChannelPattern_ClassDiagram.puml*) outlines key components:
- **Channel**: Represents a processing pipeline that acquires sensor data, transforms it, and drives an actuator.
- **ConcreteTransformChecker**: Associated with a channel, this class checks the validity of the channel’s output. It maintains links to both the active channel (itsChannel) and the alternative channel (itsOtherChannel) to enable channel switching.
- **SensorDeviceDriver & ActuatorDeviceDriver**: Provide the physical interface for data acquisition and actuation.
- **ConcreteDataTransform**: Implements specific data transformation steps within the channel.

*Explanation:*  
The Channel aggregates various processing objects (data transforms, sensor and actuator drivers) to form an end-to-end processing chain. The ConcreteTransformChecker monitors the transformation chain. Its dual associations (to the active and the alternative channel) enable the system to disable the faulty channel and switch to the backup channel when necessary.

### Sequence Diagram
The sequence diagram (see *DualChannelPattern_SequenceDiagram.puml*) illustrates the following flow:
1. A client invokes the channel’s data acquisition service.
2. The active channel (itsChannel) acquires raw sensor data.
3. Data is processed step by step (through the data transforms).
4. The ConcreteTransformChecker evaluates the output. If the output meets validation criteria, the result is forwarded to the actuator; otherwise, the checker disables the active channel and enables the alternative channel (itsOtherChannel) to take over.
5. The actuator device driver then receives the final output for actuation.

*Explanation:*  
This flow demonstrates how the Dual Channel Pattern detects faults in the active channel and seamlessly switches to the alternative channel, ensuring continued reliable operation even in the presence of a fault.

## Usage Guidelines
- **For Understanding:**  
  Review the class diagram for the structural relationships between channels, transform checkers, and drivers. Examine the sequence diagram to see how data flows and how channel switching is performed.
- **For Implementation:**  
  Implement the channel processing pipeline with clear links between sensor acquisition, data transformation, and actuator output. Use the transform checker for redundancy management and fault detection.

## Integration with Code
The diagrams correspond to the following implementation files:
- `Channel` classes for data transformation and actuation.
- `ConcreteTransformChecker` for validating the channel output.
- `SensorDeviceDriver` and `ActuatorDeviceDriver` for hardware interfacing.

## Commands
```bash
gcc -o DualChannelPattern.exe dualChannelPattern.c SensorDeviceDriver.c ActuatorDeviceDriver.c ConcreteDataTransform.c ConcreteTransformChecker.c ...existing code...
./DualChannelPattern.exe
```