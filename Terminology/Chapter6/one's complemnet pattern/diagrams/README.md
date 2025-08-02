# One’s Complement Pattern

## Overview
The One’s Complement Pattern is used to detect memory corruption by storing critical data in two forms: the original and its bit-wise (one’s) complement. When the data are read back, the complement is inverted and compared to the original value. If they match, the data is considered intact; if not, an error handler is triggered, typically invoking an AlarmManager.

## Diagram Overview

### Class Diagram
- **OnesCompProtectedDataElement:**  
  Stores the data (e.g., in OwnShipAttitude) in normal and inverted forms and implements methods to set and retrieve the data. It calls an error handler if a discrepancy is found.
- **AlarmManager:**  
  Handles errors by, for example, raising an alarm when data corruption is detected.
- **DataClient:**  
  Represents the client that interacts with the protected data element.

*Explanation:*  
The class diagram (see *ClassDiagram.puml* below) shows that the OnesCompProtectedDataElement maintains two copies of the data. When a client retrieves the data, the element inverts the stored complement and compares this with the normal copy. A mismatch indicates corruption, and the AlarmManager is notified.

### Sequence Diagram
- **Flow:**  
  1. The DataClient calls the getData() method on the OnesCompProtectedDataElement.
  2. The element reinverts its stored complement.
  3. It compares the result to the normal stored data.
  4. If the values match, the data is returned; otherwise, an error is reported via the AlarmManager.
  
*Explanation:*  
The sequence diagram (see *SequenceDiagram.puml* below) clarifies the verification process performed during data retrieval. This ensures that any bit-level corruption is identified immediately before the data is used.

## Usage Guidelines
- Use the Class Diagram to review the structural relationships between the protected data element, the AlarmManager, and the client.
- Consult the Sequence Diagram to understand the step-by-step data verification and error handling process.
- This pattern is ideal for small sets of critical data where memory overhead for replication is acceptable.

## Integration with Code
The diagrams correspond to:
- `OwnShipAttitude.h/.c` (as an example implementation of OnesCompProtectedDataElement)
- `AlarmManager.h/.c`
- The DataClient code that uses the protected element

## Commands
```bash
gcc -o OnesComplementPattern.exe OwnShipAttitude.c AlarmManager.c ...existing code...
./OnesComplementPattern.exe
```