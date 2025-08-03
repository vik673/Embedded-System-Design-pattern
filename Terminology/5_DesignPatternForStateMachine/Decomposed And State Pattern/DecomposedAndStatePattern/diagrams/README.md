# Decomposed AND-State Pattern - UML Diagrams

This directory contains the complete UML documentation for the Decomposed AND-State Pattern implementation, including class diagrams, sequence diagrams, and specialized interaction diagrams.

## Diagram Overview

### 1. State Diagram (`StateDiagram.puml`)
**Purpose**: Defines the state machine structure with orthogonal regions
- **High-level states**: OFF_STATE, ON_STATE, EMERGENCY_STATE
- **Orthogonal regions**: ErrorStatus and ModeStatus within ON_STATE
- **Concurrent transitions**: Shows how events affect different regions independently
- **Guard conditions**: Emergency transition requires both ERROR_STATE AND OPERATIONAL_STATE

### 2. Class Diagram (`ClassDiagram.puml` & `diagrams/DecomposedAndStatePattern_ClassDiagram.puml`)
**Purpose**: Shows the complete class structure and relationships
- **Context Class**: `LightController` manages high-level states and coordinates regions
- **AND-State Classes**: `ErrorStateClass` and `ModeStateClass` implement orthogonal regions
- **Container Class**: `AndStateList` manages collections of orthogonal regions
- **Device Classes**: `Light` and `Klaxon` provide the controlled hardware interface
- **Support Classes**: Function pointers, enums, and utility classes

### 3. Main Sequence Diagram (`SequenceDiagram.puml` & `diagrams/DecomposedAndStatePattern_SequenceDiagram.puml`)
**Purpose**: Demonstrates complete system lifecycle and interactions
- **Initialization**: System setup and region creation
- **State Transitions**: OFF → ON → EMERGENCY → OFF
- **Event Delegation**: How events are broadcast to all regions
- **Concurrent Processing**: Multiple regions handling events simultaneously
- **Guard Conditions**: Complex transitions requiring multiple region states

### 4. Event Delegation Diagrams (`EventDelegationSequence.puml` & `diagrams/DecomposedAndStatePattern_EventDelegation.puml`)
**Purpose**: Focus on the core pattern mechanism - event delegation
- **Broadcasting Strategy**: Events sent to all active regions
- **Independent Processing**: Each region handles events according to its state
- **Result Consolidation**: Context combines results from all regions
- **Guard Evaluation**: Using state information from multiple regions

## Key Pattern Features Illustrated

### 1. Decomposition
- **Separation of Concerns**: Error handling and mode management are separate classes
- **Independent Evolution**: Each region can change state independently
- **Loose Coupling**: Regions don't directly communicate with each other

### 2. Event Delegation
- **Broadcast Pattern**: Events are sent to all relevant regions
- **Concurrent Processing**: Multiple regions process the same event simultaneously
- **Selective Response**: Only regions with defined transitions respond

### 3. Guard Conditions
- **Cross-Region Dependencies**: Transitions can depend on states in multiple regions
- **Complex Logic**: Boolean combinations of region states
- **Coordinated Behavior**: High-level behavior emerges from region interactions

### 4. Dynamic Management
- **Region Lifecycle**: Regions are created/destroyed as needed
- **State Persistence**: Region states are maintained independently
- **Reset Capability**: All regions can be synchronized to default states

## Diagram Usage Guidelines

### For Understanding the Pattern
1. Start with the **State Diagram** to understand the state machine structure
2. Review the **Class Diagram** to see the implementation architecture
3. Follow the **Main Sequence Diagram** for complete interaction flow

### For Implementation Reference
1. Use **Class Diagram** for structure and relationships
2. Reference **Event Delegation Diagrams** for event handling details
3. Apply **Sequence Diagrams** for method call sequences

### For Pattern Application
1. **State Diagram**: Define your orthogonal regions and transitions
2. **Class Diagram**: Adapt the class structure to your domain
3. **Sequence Diagrams**: Implement the event delegation mechanism

## Technical Notes

### PlantUML Features Used
- **Stereotypes**: `<<context>>`, `<<andstate>>`, `<<container>>`, `<<device>>`
- **Color Coding**: Different colors for different pattern roles
- **Notes**: Extensive documentation within diagrams
- **Grouping**: Packages for logical organization

### Consistency Elements
- **Naming Conventions**: Consistent across all diagrams
- **Color Schemes**: Same colors represent same concepts
- **Interaction Patterns**: Similar sequences across diagrams
- **Documentation Style**: Consistent note formatting

## Integration with Code

These diagrams directly correspond to the C implementation files:
- `LightController.h/.c` - Context class
- `ErrorStateClass.h/.c` - Error region implementation
- `ModeStateClass.h/.c` - Mode region implementation
- `AndStateList.h/.c` - Region container
- `Light.h/.c`, `Klaxon.h/.c` - Device classes

The diagrams serve as both design documentation and implementation reference, ensuring consistency between the conceptual model and the actual code.
