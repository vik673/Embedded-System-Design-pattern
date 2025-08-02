# UML Diagram Documentation

This folder contains UML diagrams used to represent various aspects of system design. The primary diagrams included are:

- **Class Diagram:** Shows the system structure by displaying classes, interfaces, objects, and the relationships (e.g., association, aggregation, composition, generalization) among them.
- **Sequence Diagram:** Illustrates interactions between instances (lifelines) through exchanged messages, showing the temporal order of operations.

## Class Diagram Explanation
The Class Diagram defines the structure of the system by showing:
- **Classes:** Represented as boxes containing attributes and operations (e.g., `SensorClass_getData()`).
- **Instances and Interfaces:** Instances (objects) are created from classes; interfaces specify required services.
- **Relations:** Associations (including composition and aggregation), generalizations (inheritance), and dependencies provide the interaction and connectivity between elements.

This diagram helps in understanding the overall architecture and the connections between different software elements.

## Sequence Diagram Explanation
The Sequence Diagram details how objects interact over time:
- **Lifelines:** Vertical lines representing instances of classes.
- **Messages:** Horizontal or slanted arrows depicting function calls (synchronous messages) or events (asynchronous messages).
- **Conditions:** Indicate states or attribute values at key points.
  
The sequence diagram enables tracking of method calls and interactions, clarifying the dynamic behavior of the system.

# UML Diagrams - Design Documentation

This directory contains comprehensive UML diagrams created from the UML specification document. The diagrams are created using PlantUML syntax and demonstrate various UML concepts and relationships.

## Files Overview

### 1. ClassDiagram.puml
**Purpose**: Demonstrates all major class diagram components
**Contains**:
- Classes with attributes and operations
- Interfaces and abstract classes
- Enumerations and value objects
- All relationship types (association, composition, aggregation, generalization, realization, dependency)
- Visibility modifiers and multiplicities
- Comments and annotations

**Key Components**:
- `SensorClass` - Main class implementing sensor interface pattern
- `SensorController` - Controller managing multiple sensors
- `DataLogger` - Data persistence component
- `SensorInterface` - Interface specification
- `Device` - Abstract base class
- `DeviceStatus` - Enumeration type

### 2. SequenceDiagram.puml
**Purpose**: Shows message flow and time-ordered interactions
**Contains**:
- Lifelines representing object instances
- Synchronous and asynchronous messages
- Activation boxes showing object activity
- Alternative flows (alt/else)
- Optional interactions (opt)
- Condition marks and comments

**Scenario**: Sensor data collection process with error handling

### 3. StateDiagram.puml
**Purpose**: Demonstrates state machine behavior and transitions
**Contains**:
- Simple and composite states
- OR-states and AND-states (concurrent regions)
- Entry, exit, and transition actions
- Internal transitions
- Guards and event triggers
- Pseudostates (fork, join, choice, terminal)
- Default transitions

**Models**: Complete sensor device lifecycle from initialization to decommissioning

### 4. UMLOverview.puml
**Purpose**: High-level overview of UML diagram types and their relationships
**Contains**:
- Structural vs. behavioral diagram categories
- Key elements of each diagram type
- Relationships between different UML diagrams
- How diagrams complement each other

### 5. RelationshipExamples.puml
**Purpose**: Detailed examples of all UML relationship types
**Contains**:
- Association with navigation and multiplicity
- Composition (strong ownership)
- Aggregation (weak ownership)
- Generalization (inheritance)
- Realization (interface implementation)
- Dependency (usage)
- Visibility modifiers demonstration
- Multiplicity notation examples

## How to View the Diagrams

### Method 1: VS Code with PlantUML Extension
1. Install the PlantUML extension in VS Code
2. Install Java (required for PlantUML)
3. Open any `.puml` file
4. Press `Alt+D` or use the preview pane to render the diagram

### Method 2: Online PlantUML Editor
1. Go to [PlantUML Online Server](http://www.plantuml.com/plantuml/uml/)
2. Copy the content from any `.puml` file
3. Paste it into the online editor
4. View the rendered diagram

### Method 3: Command Line
1. Install PlantUML JAR file
2. Run: `java -jar plantuml.jar DiagramName.puml`
3. This generates PNG/SVG files

### Method 4: Export as Images
The diagrams can be exported to various formats:
- PNG (for documentation)
- SVG (for scalable graphics)
- PDF (for printing)
- LaTeX (for academic papers)

## UML Concepts Demonstrated

### Class Diagram Concepts
- **Classes**: Software elements with attributes and operations
- **Interfaces**: Service specifications without implementation
- **Abstract Classes**: Partial implementations for inheritance
- **Enumerations**: Type-safe constant definitions
- **Visibility**: Public (+), Protected (#), Private (-), Package (~)
- **Static Members**: Class-level attributes and operations
- **Abstract Members**: Must be implemented by subclasses

### Relationship Types
1. **Association**: "uses" or "has" relationship
   - Navigable connections between classes
   - Implemented as pointers or references
   - Can be unidirectional or bidirectional

2. **Composition**: "part-of" relationship (strong)
   - Whole controls lifecycle of parts
   - Parts cannot exist without whole
   - Filled diamond notation

3. **Aggregation**: "part-of" relationship (weak)
   - Parts can exist independently
   - Whole doesn't control part lifecycle
   - Empty diamond notation

4. **Generalization**: "is-a" relationship
   - Inheritance from general to specific
   - Feature inheritance (attributes, operations, relations)
   - Triangle arrow pointing to superclass

5. **Realization**: Interface implementation
   - Class fulfills interface contract
   - Dashed line with triangle arrow
   - No implementation inheritance

6. **Dependency**: "uses" relationship
   - Compilation or runtime dependency
   - Often temporary (parameter, local variable)
   - Dashed arrow with open arrowhead

### State Diagram Concepts
- **States**: Conditions or situations during object lifetime
- **Transitions**: Responses to events while in specific states
- **Events**: Triggers that can cause state changes
- **Guards**: Boolean conditions that must be true for transitions
- **Actions**: Behaviors executed during transitions or within states
- **Entry/Exit Actions**: Executed when entering/leaving states
- **Internal Transitions**: Actions without state changes
- **Composite States**: States containing nested substates
- **Concurrent States**: Multiple state machines running simultaneously

### Sequence Diagram Concepts
- **Lifelines**: Vertical lines representing object instances
- **Messages**: Horizontal arrows showing interactions
- **Activation Boxes**: Rectangles showing when objects are active
- **Synchronous Messages**: Solid arrows (function calls)
- **Asynchronous Messages**: Open arrows (events, signals)
- **Self-Messages**: Object calling its own methods
- **Condition Marks**: Hexagons showing state or variable values

## Best Practices Demonstrated

1. **Naming Conventions**:
   - Classes: PascalCase (e.g., `SensorClass`)
   - Attributes: camelCase (e.g., `sensorId`)
   - Operations: camelCase with descriptive names
   - Constants: UPPER_CASE (e.g., `MAX_SENSORS`)

2. **Operation Naming for Embedded Systems**:
   - Format: `<ClassName>_<OperationName>`
   - Example: `SensorClass_getData()`
   - First parameter is pointer to class instance

3. **Relationship Guidelines**:
   - Use composition for "part-of" relationships where parts can't exist independently
   - Use aggregation for collections where parts have independent lifecycle
   - Use association for general "uses" or "knows about" relationships
   - Use dependency for temporary or compilation-time relationships

4. **State Machine Design**:
   - Keep states focused on single concerns
   - Use composite states to manage complexity
   - Include error handling and recovery paths
   - Document entry/exit actions clearly
   - Use guards to prevent invalid transitions

## Integration with Embedded Systems

These diagrams follow embedded systems design patterns:

1. **Resource Management**: Clear ownership through composition/aggregation
2. **Error Handling**: Explicit error states and recovery mechanisms
3. **Concurrency**: AND-states for modeling parallel behaviors
4. **Interface Segregation**: Small, focused interfaces
5. **Dependency Management**: Clear compilation dependencies
6. **Lifecycle Management**: Explicit initialization and shutdown sequences

## Extending the Diagrams

To create your own diagrams based on these examples:

1. Start with the relationship examples to understand syntax
2. Copy relevant sections for your specific use case
3. Modify class names, attributes, and operations
4. Adjust relationships and multiplicities
5. Add domain-specific comments and notes
6. Validate the design against your requirements

## Tools and Dependencies

- **PlantUML**: Diagram rendering engine
- **Java 8+**: Required runtime for PlantUML
- **Graphviz** (optional): Enhanced layout algorithms
- **VS Code PlantUML Extension**: For integrated editing and preview

## References

- [PlantUML Official Documentation](https://plantuml.com/)
- [UML 2.5 Specification](https://www.omg.org/spec/UML/)
- [Embedded UML Design Patterns](https://www.embedded.com/uml-for-embedded-systems/)
