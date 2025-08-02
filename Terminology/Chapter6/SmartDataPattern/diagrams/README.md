# Smart Data Pattern

## Overview
The Smart Data Pattern enhances the robustness of embedded systems by ensuring that critical scalar data are self-checking. In this pattern, data are stored along with their one’s complement version; when retrieved, the inverted complement is compared to the original. A mismatch indicates memory corruption caused by EMI, hardware faults, or other issues. This defensive design approach prevents silent errors and encourages error detection at runtime.

## Diagram Overview

### Class Diagram
The class diagram (see *ClassDiagram.puml* below) shows:
- **SmartDataType** (illustrated here by SmartInt and SmartColor):  
  Each smart data type tracks its value and valid range. It offers methods to set and get the data while checking for range errors. When the value is set, its one’s complement is computed and stored. Upon retrieval, the stored complement is re-inverted and compared to the original value.
- **AlarmManager:**  
  Receives notifications when data integrity checks fail.
- **DataClient (e.g., PatientDataClass):**  
  Uses these smart data types to hold critical parameters (like age, weight, heart rate, and color settings) ensuring that any corruption is detected immediately.

*Explanation:*  
This design encapsulates the verification logic within the smart data type. By duplicating the data (one in its normal form and one as its bit-wise complement), the Smart Data Pattern makes error detection intrinsic to data access—without requiring explicit external checks.

### Sequence Diagram
The sequence diagram (see *SequenceDiagram.puml* below) illustrates the following flow:
1. A DataClient calls a getter (e.g., SmartInt_getPrimitive) on a smart data instance.
2. The smart data type inverts its stored complement.
3. It compares the re-inverted value with the normal stored value.
4. If the values match, the data is returned; otherwise, the AlarmManager is notified (via an error handler) and an error is reported.

*Explanation:*  
This sequence clearly demonstrates how every data retrieval is validated. The atomic check ensures that any corruption is immediately detected and handled, making the smart data type self-protecting.

## Usage Guidelines
- Use the Class Diagram as a blueprint for implementing self-checking data types.
- Follow the Sequence Diagram to integrate runtime checks in critical data flows.
- The pattern is ideal for systems with safety-critical data where silent data corruption could have severe consequences.

## Integration with Code
The diagrams correlate with the implementation of:
- `SmartInt.h/.c` and `SmartColor.h/.c` (which implement SmartDataType functionality)
- `PatientDataClass.h/.c` (a client of the smart data types)
- `AlarmManager.h/.c` for error handling.

## Commands
```bash
gcc -o SmartDataPattern.exe SmartInt.c SmartColor.c PatientDataClass.c AlarmManager.c ...existing code...
./SmartDataPattern.exe
```
├── SmartColor.h/.c        # Smart color enumeration data type
├── PatientDataClass.h/.c  # Example server class using smart types
├── demo.c                 # Demonstration program
└── Makefile              # Build configuration

diagrams/
├── class_diagram.puml           # UML class diagram
├── sequence_diagram.puml        # UML sequence diagram
└── pattern_structure_diagram.puml # Pattern structure diagram
```

## Key Features

### SmartInt
- Wraps primitive `int` type with range checking
- Configurable low and high boundaries
- Automatic error reporting via AlarmManager
- Self-validating operations

### SmartColor
- Wraps `ColorType` enumeration with range checking
- Validates color values within defined ranges
- Integrated error handling

### PatientDataClass
- Example server class demonstrating pattern usage
- Contains multiple smart data types (age, weight, heart rate, colors)
- Provides validation for all contained data

### AlarmManager
- Centralized error management system
- Tracks error counts and current alarm status
- Provides descriptive error messages
- Console output for debugging

## Building and Running

### Prerequisites
- GCC compiler
- Make utility
- (Optional) PlantUML for diagram generation

### Build Instructions

```bash
# Navigate to implementation directory
cd implementation/

# Build the project
make

# Run the demonstration
make run

# Clean build files
make clean
```

### Windows Build (PowerShell)
```powershell
# Navigate to implementation directory
cd implementation/

# Compile manually if make is not available
gcc -Wall -Wextra -std=c99 -g -c AlarmManager.c -o AlarmManager.o
gcc -Wall -Wextra -std=c99 -g -c SmartInt.c -o SmartInt.o
gcc -Wall -Wextra -std=c99 -g -c SmartColor.c -o SmartColor.o
gcc -Wall -Wextra -std=c99 -g -c PatientDataClass.c -o PatientDataClass.o
gcc -Wall -Wextra -std=c99 -g -c demo.c -o demo.o
gcc *.o -o smart_data_demo.exe

# Run the demo
./smart_data_demo.exe
```

## Usage Examples

### Basic Usage
```c
#include "PatientDataClass.h"
#include "AlarmManager.h"

int main() {
    // Create alarm manager
    AlarmManager* alarmMgr = AlarmManager_Create();
    
    // Create patient data with smart types
    PatientDataClass* patient = PatientDataClass_Create(alarmMgr);
    
    // Set valid values (no alarms)
    PatientDataClass_setAge(patient, 35);        // Valid: 0-130
    PatientDataClass_setWeight(patient, 75);     // Valid: 0-500
    PatientDataClass_setHeartRate(patient, 72);  // Valid: 0-400
    
    // Set invalid values (triggers alarms)
    PatientDataClass_setAge(patient, 150);       // Invalid: > 130
    PatientDataClass_setWeight(patient, 600);    // Invalid: > 500
    
    // Check data validity
    ErrorCodeType result = PatientDataClass_checkAllData(patient);
    
    // Clean up
    PatientDataClass_Destroy(patient);
    AlarmManager_Destroy(alarmMgr);
    
    return 0;
}
```

### Creating Custom Smart Types
```c
// Define your smart type structure
struct SmartTemperature {
    ErrorCodeType errorCode;
    float highRange;
    float lowRange;
    float value;
    AlarmManager* itsAlarmManager;
};

// Implement validation logic
ErrorCodeType SmartTemperature_setPrimitive(SmartTemperature* me, float temp) {
    me->errorCode = NO_ERRORS;
    if (temp < me->lowRange) {
        me->errorCode = BELOW_RANGE;
        AlarmManager_addAlarm(me->itsAlarmManager, me->errorCode);
    } else if (temp > me->highRange) {
        me->errorCode = ABOVE_RANGE;
        AlarmManager_addAlarm(me->itsAlarmManager, me->errorCode);
    } else {
        me->value = temp;
    }
    return me->errorCode;
}
```

## Diagrams

### Class Diagram
Shows the static structure of the pattern implementation including all classes, their attributes, methods, and relationships.

### Sequence Diagram
Illustrates the dynamic behavior during execution, showing how objects interact during valid operations and error scenarios.

### Pattern Structure Diagram
Depicts the pattern roles and their relationships, along with the concrete implementation mapping.

## Benefits

1. **Defensive Programming**: Automatic validation prevents invalid data from propagating
2. **Error Detection**: Cannot ignore error conditions - they're built into the data types
3. **Debugging Aid**: Clear error messages and alarm tracking
4. **Code Safety**: Similar to Ada's runtime checking but in C
5. **Maintainability**: Centralized validation logic
6. **Reusability**: Pattern can be applied to any data type

## Trade-offs

### Advantages
- Self-protecting data with automatic checking
- Centralized error handling
- Clear error reporting
- Defensive programming enforcement

### Disadvantages
- Performance overhead for validation operations
- Additional memory usage for range and error information
- Possible circumvention if programmers access data directly
- Increased code complexity

## Pattern Extensions

The pattern can be extended to include:
- **Unit-aware types**: Handle conversions between different units (currency, mass, distance)
- **Relationship validation**: Check consistency between related data elements
- **Logging integration**: Enhanced error tracking and audit trails
- **Configuration-driven ranges**: Runtime configurable validation ranges

## Related Patterns

- **Smart Pointer Pattern**: Extends the concept to pointer types
- **State Pattern**: For more complex validation state machines
- **Observer Pattern**: For notification of data changes and errors

## Testing

The demo program tests:
- Valid value assignments
- Range violation detection
- Error reporting and alarm management
- Data validation across multiple smart types
- Memory management (creation/destruction)

## Contributing

When extending this implementation:
1. Follow the established naming conventions
2. Ensure all functions check for NULL pointers
3. Add appropriate error handling
4. Update documentation and diagrams
5. Add test cases for new functionality

## License

This implementation is provided as an educational example of the Smart Data Pattern for embedded systems development.
